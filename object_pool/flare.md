## 对象池

why use?

https://github.com/Tencent/flare/blob/master/flare/doc/object-pool.md

## 使用

我们来见一个例子


## 

```cpp
// Note that this pool uses thread-local cache. That is, it does not perform
// well in scenarios such as producer-consumer (in this case, the producer
// thread keeps allocating objects while the consumer thread keeps de-allocating
// objects, and nothing could be reused by either thread.). Be aware of this.

// You need to customize these parameters before using this object pool.
template <class T>
struct PoolTraits {
  // Type of backend pool to be used for this type. Check comments in `PoolType`
  // for their explanation.
  //
  // static constexpr PoolType kType = ...;  // Or `kPoolType`?

  // If your type cannot be created by `new T()`, you can provide a factory
  // here.
  //
  // Leave it undefined if you don't need it.
  //
  // static T* Create() { ... }

  // If you type cannot be destroyed by `delete ptr`, you can provide a
  // customized deleter here.
  //
  // Leave it undefined if you don't need it.
  //
  // void Destroy(T* ptr) { ... }

  // Below are several hooks.
  //
  // For those hooks you don't need, leave them as not defined.

  // Hook for `Get`. It's called after an object is retrieved from the pool.
  // This hook can be used for resetting objects to a "clean" state so that
  // users won't need to reset objects themselves.
  //
  // static void OnGet(T*) { ... }

  // Hook for `Put`. It's called before an object is put into the pool. It can
  // be handy if you want to release specific precious resources (handle to
  // temporary file, for example) before the object is hold by the pool.
  //
  // static void OnPut(T*) { ... }

  // For type-specific arguments, see header for the corresponding backend.

  // ... TODO

  static_assert(sizeof(T) == 0,
                "You need to specialize `flare::object_pool::PoolTraits` to "
                "specify parameters before using `object_pool::Xxx`.");
};
```

这里有几个比较重要的点

1. 每一种需要放入内存池的结构，我们都需要特化一下

why design like this？

2. PoolType

这里实现了集中内存池类型

```cpp
// For the moment, only `MemoryNodeShared` is highly optimized, and it likely
// will outperform all other type of pools.
enum class PoolType {
  // Do not use object pool at all.
  //
  // This type is normally used for debugging purpose. (Object pooling makes it
  // hard to tracing object creation, by disabling it, debugging can be easier.)
  Disabled,

  // Cache objects in a thread local cache.
  //
  // This type has the highest performance if your object allocation /
  // deallocation is done evenly in every thread.
  //
  // No lock / synchronization is required for this type of pool
  ThreadLocal,

  // Cache a small amount of objects locally, and use a shared pool for threads
  // in the same NUMA Node.
  //
  // If your objects is allocated in one thread, but freed in other threads in
  // the same scheduling group. This type of pool might work better.
  MemoryNodeShared,

  // Cache a small amount of objects locally, and the rest are cached in a
  // global pool.
  //
  // This type of pool might work not-as-good as the above ones, but if your
  // workload has no evident allocation / deallocation pattern, this type might
  // suit most.
  Global
};
```

3. Create

自定义的一个工厂

4. Destroy

自定义如何销毁

解下来就是几个最为核心的hooks

5. OnGet

todo : 不理解This hook can be used for resetting objects to a "clean" state so that users won't need to reset objects themselves.

6. OnPut

## Get

```cpp
// Get an object from the corresponding backend.
template <class T>
inline void* Get() {
  auto rc = GetWithoutHook<T>();
  OnGetHook<T>(rc);
  return rc;
}
```

## GetWithoutHook

```cpp
// Call corresponding backend to get an object. Hook is not called.
template <class T>
inline void* GetWithoutHook() {
  constexpr auto kType = PoolTraits<T>::kType;

  if constexpr (kType == PoolType::Disabled) {
    return disabled::Get(*GetTypeDesc<T>());
  } else if constexpr (kType == PoolType::ThreadLocal) {
    return tls::Get(*GetTypeDesc<T>(), tls::GetThreadLocalPool<T>());
  } else if constexpr (kType == PoolType::MemoryNodeShared) {
    return memory_node_shared::Get<T>();
  } else if constexpr (kType == PoolType::Global) {
    return global::Get(*GetTypeDesc<T>());
  } else {
    static_assert(sizeof(T) == 0, "Unexpected pool type.");
    FLARE_CHECK(0);
  }
}
```

编译期通过kType决定来调用哪一个Get

我们简单看一个disabled::Get例子，其他的在后续各个type中详解

```cpp
void* Get(const TypeDescriptor& desc) {
  auto rc = desc.create();
  return rc;
}
```

主要还是TypeDescriptor

## GetTypeDesc

这个顾名思义，就是获取信息描述，其中一个是type信息，还有两个callback : create /destroy, 在我们特化的时候可以写我们的特定版本

还有个是类型信息，不过不是很重要，我们放在最后讲

```cpp
template <class T>
const TypeDescriptor* GetTypeDesc() {
  // `constexpr` doesn't work here.
  //
  // Possibly related: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81933
  static const TypeDescriptor desc = {.type = GetTypeIndex<T>(),
                                      .create = CreateObject<T>,
                                      .destroy = DestroyObject<T>};
  return &desc;
}
```

```cpp
struct TypeDescriptor {
  TypeIndex type;

  void* (*create)();
  void (*destroy)(void*);

  // Get / Put hook are called directly via `detail::OnXxxHook`. This eliminates
  // an indirect function call.
  //
  // So no `on_get` / `on_put` function pointer here.
};
```

###  CreateObject

```cpp
// Call user defined factory if present, `new T()` otherwise.
template <class T>
void* CreateObject() {
  if constexpr (FLARE_INTERNAL_IS_VALID(&x.Create)(PoolTraits<T>{})) {
    return PoolTraits<T>::Create();
  } else {
    return new T();
  }
}
```

```cpp
// `x` should be used as placeholder's name in` expr`.
#define FLARE_INTERNAL_IS_VALID(expr) \
  ::flare::internal::is_valid([](auto&& x) -> decltype(expr) {})
```

宏展开后就看得出这上面无厘头的x是咋回事了

```cpp
FLARE_INTERNAL_IS_VALID(&x.Create)

--> 

::flare::internal::is_valid([](auto&& x) -> decltype(&x.Create) {})

// x是PoolTraits<T>{}
```

```cpp
template <class F>
constexpr auto is_valid(F&& f) {
  return [f = std::forward<F>(f)](auto&&... args) constexpr {
    // FIXME: Perfect forwarding.
    return std::is_invocable_v<F, decltype(args)...>;
  };
}
```

https://en.cppreference.com/w/cpp/types/is_invocable

### DestroyObject

```cpp
// Call user defined deleter if present, `delete static_cast<T*>(ptr)`
// otherwise.
template <class T>
void DestroyObject(void* ptr) {
  auto p = static_cast<T*>(ptr);
  if constexpr (FLARE_INTERNAL_IS_VALID(&x.Destroy)(PoolTraits<T>{})) {
    PoolTraits<T>::Destroy(p);
  } else {
    delete p;
  }
}
```

destroy和create同理

总结下就是，你在特化的时候定义了合理的create和destroy，如果没有定义custom的方法，则调用new和delete

## TypeIndex

dsec里面还有个type信息

```cpp
template <class T>
constexpr TypeIndex GetTypeIndex() {
  return TypeIndex(&detail::kTypeIndexEntity<T>);
}
```

```cpp
template <class T>
inline const TypeIndexEntity kTypeIndexEntity{std::type_index(typeid(T))};
```

```cpp
// For each type, there is only one instance of `TypeIndexEntity`. `TypeIndex`
// keeps a reference to the entity, which is used for comparison and other
// stuff.
struct TypeIndexEntity {
  std::type_index runtime_type_index;
};
```

```cpp
// Due to QoI issue in libstdc++, which uses `strcmp` for comparing
// `std::type_index`, we roll our own.
//
// Note our own does NOT support runtime type, only compile time type is
// recognized.
class TypeIndex {
 public:
  constexpr TypeIndex() noexcept : entity_(nullptr) {}

  // In case you need `std::type_index` of the corresponding type, this method
  // is provided for you convenience.
  //
  // Keep in mind, though, that this method can be slow. In most cases you
  // should only use it for logging purpose.
  std::type_index GetRuntimeTypeIndex() const {
    return entity_->runtime_type_index;
  }

  constexpr bool operator==(TypeIndex t) const noexcept {
    return entity_ == t.entity_;
  }
  constexpr bool operator!=(TypeIndex t) const noexcept {
    return entity_ != t.entity_;
  }
  constexpr bool operator<(TypeIndex t) const noexcept {
    return entity_ < t.entity_;
  }

  // If C++20 is usable, you get all other compriason operators (!=, <=, >, ...)
  // automatically. I'm not gonna implement them as we don't use them for the
  // time being.

 private:
  template <class T>
  friend constexpr TypeIndex GetTypeIndex();
  friend struct std::hash<TypeIndex>;

  constexpr explicit TypeIndex(const detail::TypeIndexEntity* entity) noexcept
      : entity_(entity) {}

 private:
  const detail::TypeIndexEntity* entity_;
};
```

这个就是存储了类型信息，在后续获取类型名称使用

```cpp
std::unique_ptr<GlobalPoolDescriptor> CreateGlobalPoolDescriptor(
    const TypeDescriptor& desc, std::size_t min_blocks_per_node,
    std::size_t max_blocks_per_node, std::chrono::nanoseconds max_idle,
    std::size_t transfer_threshold, std::size_t transfer_batch_size) {
  auto type_name = Demangle(desc.type.GetRuntimeTypeIndex().name());
  ...
}
```

- tips : typeid/std::type_index/std::type_info

https://en.cppreference.com/w/cpp/types/type_index

https://www.zhihu.com/question/38997922

https://www.zhihu.com/question/53916400

https://zhuanlan.zhihu.com/p/32182911

https://blog.csdn.net/audi2/article/details/104014908


## OnGetHook

struct PoolTraits 中还可以自定义 OnGet/OnPut, 分别为Get的hook和Put的hook，原理相同，我们这里看看get

It's called after an object is retrieved from the pool.

```cpp
// Get an object from the corresponding backend.
template <class T>
inline void* Get() {
  auto rc = GetWithoutHook<T>();
  OnGetHook<T>(rc);
  return rc;
}
```

从get调用可以看出他这个顺序

### OnGetHook

```cpp
// These hook helpers detect if the corresponding hook was set, and call the
// hook if so. It's a no-op otherwise.
#define FLARE_DEFINE_OBJECT_POOL_HOOK_IMPL(HookName)                       \
  template <class T>                                                       \
  inline void HookName##Hook([[maybe_unused]] void* p) {                   \
    if constexpr (FLARE_INTERNAL_IS_VALID(&x.HookName)(PoolTraits<T>{})) { \
      return PoolTraits<T>::HookName(reinterpret_cast<T*>(p));             \
    }                                                                      \
  }
FLARE_DEFINE_OBJECT_POOL_HOOK_IMPL(OnGet)
FLARE_DEFINE_OBJECT_POOL_HOOK_IMPL(OnPut)
#undef FLARE_DEFINE_OBJECT_POOL_HOOK_IMPL
```

我们展开看看

```cpp
template <class T> 
inline void OnGetHook([[maybe_unused]] void* p) {
    if constexpr (FLARE_INTERNAL_IS_VALID(&x.HookName)(PoolTraits<T>{})) {
        return PoolTraits<T>::OnGet(reinterpret_cast<T*>(p));  
    }
}
```

## 空实现: Disabled

例子

```cpp
int alive = 0;

struct C {
  C() { ++alive; }
  ~C() { --alive; }
};

template <>
struct PoolTraits<C> {
  static constexpr auto kType = PoolType::Disabled;
};

int main()
{
  std::vector<PooledPtr<C>> ptrs;
  for (int i = 0; i != 1000; ++i) {
    ptrs.push_back(Get<C>());
  }
  ASSERT_EQ(1000, alive);
  ptrs.clear();
  ASSERT_EQ(0, alive);
  Get<C>();
  ASSERT_EQ(0, alive);
}
```

```cpp
void* Get(const TypeDescriptor& desc) {
  auto rc = desc.create();
  return rc;
}

void Put(const TypeDescriptor& desc, void* ptr) { desc.destroy(ptr); }
```

只是简单的来创建和销毁，不做任何事情

注意使用是Get是创建，Put是销毁。

主要是用于debug

## 线程局部缓存

这个实现严格的在线程内复用对象，因此其没有共享数据的同步开销，性能最高。但是另一方面，这个实现对于线程间频繁迁移且迁入迁出数据量不对等之类的情况不适用。

对于单线程执行业务逻辑（多线程用于并发处理请求，而不是多线程用于加速单个请求）的情况（大多数服务属于此类），如果各个请求的工作集及处理逻辑相似，可以优先考虑这一对象池。

这种对象池至少会保留PoolTraits<T>::kLowWaterMark个对象存活，除此之外，如果当前线程局部的对象池数量尚未超过PoolTraits<T>::kHighWaterMark，那么对于被释放尚不足PoolTraits<T>::kMaxIdle时长的对象，会保留下来备用，否则将会被释放。

我们看看使用说明

```cpp
// Extra requirement on `PoolTraits<T>`:
//
// ```
// Minimum free objects cached per thread.
//
// Note that that parameter only affects idle objects (@sa `kMaxIdle`). For
// objects that are fresh enough, they're always kept regardless of this
// parameter. (This means there are always at least `kLowWaterMark + 1`
// objects alive though, as cache washing is triggered by `Put`, and the
// object just `Put`-ed is always fresh, and won't be freed.).
//
// static constexpr std::size_t kLowWaterMark = ...;
//
// Maximum free objects cached per thread. If you don't want to set a threshold,
// use `std::numeric_limits<std::size_t>::max()`.
//
// This parameter also affects fresh objects. Objects are freed if there are
// more than `kHighWaterMark` objects alive regardless of their freshness.
//
// static constexpr std::size_t kHighWaterMark = ...;
//
// Quiet period before an object is eligible for removal (when there are more
// than `kLowWaterMark` idle objects are cached). Note that the implementation
// may delay object deallocation longer than this option.
//
// static constexpr std::chrono::nanoseconds kMaxIdle = ...;
//
// How often should the pool be purged. (TODO)
// ...
// ```
```

总结下几个参数

1. kLowWaterMark

2. kHighWaterMark

3. kMaxIdle

### Get

```cpp
void* Get(const TypeDescriptor& desc, PoolDescriptor* pool) {
  if (pool->primary_cache.empty()) {
    if (!pool->secondary_cache.empty()) {
      pool->primary_cache = std::move(pool->secondary_cache);
      // Reset the timestamp, otherwise they'll likely be moved to secondary
      // cache immediately.
      for (auto&& e : pool->primary_cache) {
        e.last_used = ReadCoarseSteadyClock();
      }
    } else {
      // We could just return the object just created instead of temporarily
      // push it into `primary_cache`. However, since we expect the pool should
      // satisfy most needs (i.e., this path should be seldom taken), this won't
      // hurt much.
      pool->primary_cache.push_back(
          TimestampedObject{.ptr = {desc.create(), desc.destroy},
                            .last_used = ReadCoarseSteadyClock()});
    }
  }
  auto rc = std::move(pool->primary_cache.back());
  pool->primary_cache.pop_back();
  return rc.ptr.Leak();
}
```

这里有两个cache，一个primary，一个secondary

如果primary不为空，则primary_cache pop出来 一个TimestampedObject

如果primary为空，但secondary_cache不为空，这个时候就把secondary转化为primary，且把他们的last_used重置，不然又马上被放到secondary去了

secondary_cache也为空，那我们则需要去create了，加入到primary中

```cpp
struct PoolDescriptor {
  const std::size_t low_water_mark;
  const std::size_t high_water_mark;
  const std::chrono::nanoseconds max_idle;
  std::chrono::steady_clock::time_point last_wash{ReadCoarseSteadyClock()};

  // Objects in primary cache is washed out to `secondary_cache` if there's
  // still room.
  std::deque<TimestampedObject> primary_cache;

  // Objects here are not subject to washing out.
  std::deque<TimestampedObject> secondary_cache;
};
```

```cpp
struct TimestampedObject {
  ErasedPtr ptr;
  std::chrono::steady_clock::time_point last_used;
};
```

```cpp
// RAII wrapper for holding type erased pointers. Type-safety is your own
// responsibility.
class ErasedPtr final {
 public:
  using Deleter = void (*)(void*);

  // A default constructed one is an empty one.
  /* implicit */ constexpr ErasedPtr(std::nullptr_t = nullptr)
      : ptr_(nullptr), deleter_(nullptr) {}

  // Ownership taken.
  template <class T>
  constexpr explicit ErasedPtr(T* ptr) noexcept
      : ptr_(ptr), deleter_([](void* ptr) { delete static_cast<T*>(ptr); }) {}
  template <class T, class D>
  constexpr ErasedPtr(T* ptr, D deleter) noexcept
      : ptr_(ptr), deleter_(deleter) {}

  // Movable
  constexpr ErasedPtr(ErasedPtr&& ptr) noexcept
      : ptr_(ptr.ptr_), deleter_(ptr.deleter_) {
    ptr.ptr_ = nullptr;
  }

  ErasedPtr& operator=(ErasedPtr&& ptr) noexcept {
    // #define FLARE_LIKELY(expr) (__builtin_expect(!!(expr), 1))
    if (FLARE_LIKELY(&ptr != this)) {
      Reset();
    }
    std::swap(ptr_, ptr.ptr_);
    std::swap(deleter_, ptr.deleter_);
    return *this;
  }

  // But not copyable.
  ErasedPtr(const ErasedPtr&) = delete;
  ErasedPtr& operator=(const ErasedPtr&) = delete;

  // Any resource we're holding is freed in dtor.
  ~ErasedPtr() {
    if (ptr_) {
      deleter_(ptr_);
    }
  }

  // Accessor.
  constexpr void* Get() const noexcept { return ptr_; }

  // It's your responsibility to check if the type match.
  template <class T>
  T* UncheckedGet() const noexcept {
    return reinterpret_cast<T*>(Get());
  }

  // Test if this object holds a valid pointer.
  constexpr explicit operator bool() const noexcept { return !!ptr_; }

  // Free any resource this class holds and reset its internal pointer to
  // `nullptr`.
  constexpr void Reset(std::nullptr_t = nullptr) noexcept {
    if (ptr_) {
      deleter_(ptr_);
      ptr_ = nullptr;
    }
  }

  // Release ownership of its internal object.
  [[nodiscard]] void* Leak() noexcept { return std::exchange(ptr_, nullptr); }

  // This is the only way you can destroy the pointer you obtain from `Leak()`.
  constexpr Deleter GetDeleter() const noexcept { return deleter_; }

 private:
  void* ptr_;
  Deleter deleter_;
};
```

所以我们看看Leak这操作

```cpp
// Release ownership of its internal object.
[[nodiscard]] void* Leak() noexcept { return std::exchange(ptr_, nullptr); }
```

### Put

```cpp
void Put(const TypeDescriptor& desc, PoolDescriptor* pool, void* ptr) {
  ScopedDeferred _([&] { WashOutCache(pool); });
  pool->primary_cache.push_back(TimestampedObject{
      .ptr = {ptr, desc.destroy}, .last_used = ReadCoarseSteadyClock()});
}
```

```cpp
// Call `F` on destruction.
template <class F>
class ScopedDeferred {
 public:
  explicit ScopedDeferred(F&& f) : action_(std::move(f)) {}
  ~ScopedDeferred() { action_(); }

  // Noncopyable / nonmovable.
  ScopedDeferred(const ScopedDeferred&) = delete;
  ScopedDeferred& operator=(const ScopedDeferred&) = delete;

 private:
  F action_;
};
```

我感觉这就是这个效果，put就是把放入primary cache中，然后执行WashOutCache

```cpp
void Put(const TypeDescriptor& desc, PoolDescriptor* pool, void* ptr) {
  pool->primary_cache.push_back(TimestampedObject{
      .ptr = {ptr, desc.destroy}, .last_used = ReadCoarseSteadyClock()});
  WashOutCache(pool);
}
```

```cpp
void WashOutCache(PoolDescriptor* pool) {
  auto now = ReadCoarseSteadyClock();
  // constexpr auto kMinimumWashInterval = 5ms;
  if (now < pool->last_wash + kMinimumWashInterval) {
    return;  // We're called too frequently.
  } else {
    pool->last_wash = now;
  }

  auto&& primary = pool->primary_cache;
  auto&& secondary = pool->secondary_cache;
  auto move_to_secondary_or_free = [&](std::size_t count) {
    while (count--) {
      if (secondary.size() < pool->low_water_mark) {
        secondary.push_back(std::move(primary.front()));
      }
      primary.pop_front();
    }
  };

  // 正如我们之前所看到特化需要提供的几个参数
  // 一个高水位标志，这里我们在washout才会去维护，所以可能是会超过的
  // 一个低水位，低水位在上面move_to_secondary_or_free中体现，维持在secondary里
  // We've reached the high-water mark, free some objects.
  if (pool->primary_cache.size() > pool->high_water_mark) {
    /*
    std::size_t GetFreeCount(std::size_t upto) {
        return std::min(upto, std::max(upto / 2, kMinimumFreePerWash));
    }
    */
    auto upto =
        GetFreeCount(pool->primary_cache.size() - pool->high_water_mark);
    move_to_secondary_or_free(upto);
    if (upto == kMinimumFreePerWash) {
      return;  // We've freed enough objects then.
    }
  }

#ifndef NDEBUG
  std::size_t objects_had =
      pool->primary_cache.size() + pool->secondary_cache.size();
#endif

  // Let's see how many objects have been idle for too long.
  auto idle_objects = std::find_if(primary.begin(), primary.end(),
                                   [&](auto&& e) {
                                     return now - e.last_used < pool->max_idle;
                                   }) -
                      primary.begin();
  move_to_secondary_or_free(GetFreeCount(idle_objects));

#ifndef NDEBUG
  if (objects_had >= pool->low_water_mark) {
    FLARE_CHECK_GE(pool->primary_cache.size() + pool->secondary_cache.size(),
                   pool->low_water_mark);
  }
#endif
}
```

这里说个细节，我们put是push_back到cache, get是从cache的back中拿出，对象的重用使用LIFO的方式，即后释放的先重用，我们期望这有利于保持缓存热度。

### PoolDescriptor

我们可以看到他还有个参数是PoolDescriptor.

```cpp
// `template <class T> inline thread_local PoolDescriptor pool` does not work:
//
// > redefinition of 'bool __tls_guard'
//
// I think it's a bug in GCC.
template <class T>
PoolDescriptor* GetThreadLocalPool() {
  static_assert(PoolTraits<T>::kHighWaterMark > PoolTraits<T>::kLowWaterMark,
                "You should leave some room between the water marks.");

  // Internally we always keep `kLowWaterMark` objects in secondary cache,
  // so the "effective" high water mark should subtract `kLowWaterMark`.
  constexpr auto kEffectiveHighWaterMark =
      PoolTraits<T>::kHighWaterMark - PoolTraits<T>::kLowWaterMark;

  FLARE_INTERNAL_TLS_MODEL thread_local PoolDescriptor pool = {
      .low_water_mark = PoolTraits<T>::kLowWaterMark,
      .high_water_mark = kEffectiveHighWaterMark,
      .max_idle = PoolTraits<T>::kMaxIdle};
  FLARE_DCHECK((pool.low_water_mark == PoolTraits<T>::kLowWaterMark) &&
                   (pool.high_water_mark == kEffectiveHighWaterMark) &&
                   (pool.max_idle == PoolTraits<T>::kMaxIdle),
               "You likely had an ODR-violation when customizing type [{}].",
               GetTypeName<T>());
  return &pool;
}
```

也看出我们的thread_local属性来源于此处，每一个thread都有一个pool

## NUMA节点内共享

看下他的参数说明

```cpp

// Extra requirement on `PoolTraits<T>`:
//
// ```
// Minimum number of objects in per node cache. Note that objects that have not
// been returned to the shared cache (e.g., in thread local cache) is not
// counted.
//
// Internally this number of rounded to a multiple of `kTransferBatchSize`.
//
// This parameter should be *significantly* greater than `kTransferBatchSize`,
// otherwise you risk allocating too many objects in each thread (as there were
// no object in the shared pool) and then bursting destroying then (as there
// would be too many objects in the shared pool). This can severely hurts
// performance. (Much worse than lock contention on the shared pool.)
//
// static constexpr std::size_t kLowWaterMark = ...;
//
// Maximum number of objects in per node cache. Objects in thread local cache is
// not counted.
//
// Rounded to a multiple of `kTransferBatchSize` internally.
//
// `kMaxIdle` (see below) is not considered if number of alive objects exceeds
// this limit.
//
// static constexpr std::size_t kHighWaterMark = ...;
//
// Minimum grace period that must have passed before an object is considered
// eligible for recycling (if the number of alive objects in shared cache does
// not exceed `kHighWaterMark`).
//
// static const std::chrono::nanoseconds kMaxIdle = ...;
//
// We also maintain a thread-local object cache for each thread. Before
// transferring objects from to shared cache (i.e., the buckets),
// `kMinimumThreadCacheSize` objects are kept locally.
//
// To disable thread-local cache, set it to 0. (The object pool will still cache
// up to `kTransferBatchSize - 1` objects before the transfer happens.).
//
// static constexpr std::size_t kMinimumThreadCacheSize = ...;
//
// For better performance, objects are transferred from thread-local cache to
// buckets in batches. This parameter specifies batch size. (If objects in
// thread local cache is not sufficient to form a batch, they're kept
// locally.).
//
// static constexpr std::size_t kTransferBatchSize = ...;
// ```
```

每个线程局部会有至多PoolTraits<T>::kMinimumThreadCacheSize个对象的缓存

每次在共享缓存和线程局部缓存之间按照PoolTraits<T>::kTransferBatchSize个对象的大小来迁移

共享缓存至少会保留PoolTraits<T>::kLowWaterMark个对象

共享缓存分块中超过PoolTraits<T>::kHighWaterMark数量、或存活时间超过PoolTraits<T>::kMaxIdle的对象会被释放

### Get

```cpp
template <class T>
inline void* Get() {
  auto&& local = descriptors_ptr<T>.local;
  if (FLARE_LIKELY(local /* Initialized */ && !local->objects.empty())) {
    // Thread local cache hit.
    return local->objects.pop_back();
  }
  return InitializeOptAndGetSlow<T>();
}
```

如果是有thread_local的object，则返回，不然初始化

```cpp
template <class T>
FLARE_INTERNAL_TLS_MODEL inline thread_local Descriptors descriptors_ptr{};
```

```cpp
struct Descriptors {
  const TypeDescriptor* type;
  GlobalPoolDescriptor* global;
  LocalPoolDescriptor* local;
};
```

```cpp
template <class T>
[[gnu::noinline]] void* InitializeOptAndGetSlow() {
  if (FLARE_UNLIKELY(!descriptors_ptr<T>.type)) {
    InitantiateEarlyInitializer<T>();
    InitializeDescriptorsSlow<T>();
  }
  auto&& [desc, global, local] = descriptors_ptr<T>;
  return GetSlow(*desc, global, local);
}
```

如果descriptors_ptr还没有type，即没有初始化，则会进行两阶段初始化

第一阶段

```cpp
template <class T>
[[gnu::noinline, gnu::cold]] void InitantiateEarlyInitializer() {
  // Instantiates `early_init_registerer`. This object will be initialized at
  // program startup, and register early initializer for us.
  [[maybe_unused]] static auto ptr = &early_init_registerer<T>;
}
```

```cpp
template <class T>
inline EarlyInitializationRegisterer<T> early_init_registerer;
```

```cpp
// Instantiation leads to registration of `T` to early initialization callback
// registry.
template <class T>
struct EarlyInitializationRegisterer {
  EarlyInitializationRegisterer() {
    RegisterEarlyInitializationCallback([] {
      InitantiateEarlyInitializer<T>();
      InitializeDescriptorsSlow<T>();
    });
  }
};
```

```cpp
void RegisterEarlyInitializationCallback(Function<void()> cb) {
  GetEarlyInitializationRegistry()->push_back(std::move(cb));
}
```

```cpp
std::vector<Function<void()>>* GetEarlyInitializationRegistry() {
  static NeverDestroyed<std::vector<Function<void()>>> registry;
  return registry.Get();
}
```

```cpp
// `NeverDestroyed<T>` helps you create objects that are never destroyed
// (without incuring heap memory allocation.).
//
// In certain cases (e.g., singleton), not destroying object can save you from
// dealing with destruction order issues.
//
// Caveats:
//
// - Be caution when declaring `NeverDestroyed<T>` as `thread_local`, this may
//   cause memory leak.
//
// - To construct `NeverDestroyed<T>`, you might have to declare this class as
//   your friend (if the constructor being called is not publicly accessible).
//
// - By declaring `NeverDestroyed<T>` as your friend, it's impossible to
//   guarantee `T` is used as a singleton as now anybody can construct a new
//   `NeverDestroyed<T>`. You can use `NeverDestroyedSingleton<T>` in this case.
//
// e.g.:
//
// void CreateWorld() {
//   static NeverDestroyed<std::mutex> lock;  // Destructor won't be called.
//   std::scoped_lock _(*lock);
//
//   // ...
// }
template <class T>
class NeverDestroyed final : private detail::NeverDestroyedImpl<T> {
  using Impl = detail::NeverDestroyedImpl<T>;

 public:
  template <class... Ts>
  explicit NeverDestroyed(Ts&&... args) {
    new (&this->storage_) T(std::forward<Ts>(args)...);
  }

  using Impl::Get;
  using Impl::operator->;
  using Impl::operator*;
};
```

```cpp
template <class T>
class NeverDestroyedImpl {
 public:
  // Noncopyable / nonmovable.
  NeverDestroyedImpl(const NeverDestroyedImpl&) = delete;
  NeverDestroyedImpl& operator=(const NeverDestroyedImpl&) = delete;

  // Accessors.
  T* Get() noexcept { return reinterpret_cast<T*>(&storage_); }
  const T* Get() const noexcept {
    return reinterpret_cast<const T*>(&storage_);
  }

  T* operator->() noexcept { return Get(); }
  const T* operator->() const noexcept { return Get(); }

  T& operator*() noexcept { return *Get(); }
  const T& operator*() const noexcept { return *Get(); }

 protected:
  NeverDestroyedImpl() = default;

 protected:
  std::aligned_storage_t<sizeof(T), alignof(T)> storage_;
};
```

这里其实就是google的`NoDestructor`


然后初始化 descriptors_ptr

```cpp
// To keep `GetDescriptors` small, we move initialization code out.
template <class T>
[[gnu::noinline]] void InitializeDescriptorsSlow() {
  descriptors_ptr<T> = {GetTypeDesc<T>(), GetGlobalPoolDescriptor<T>(),
                        GetLocalPoolDescriptor<T>()};
}
```

在线程缓存为空或溢出时，会请求或释放给NUMA节点共享的对象缓存。

```cpp
void* GetSlow(const TypeDescriptor& type, GlobalPoolDescriptor* global,
              LocalPoolDescriptor* local) {
  ScopedDeferred _([&, tsc = ReadTsc()] {
    (*global->slow_get_latency)->Report(TscElapsed(tsc, ReadTsc()));
  });

  (*global->tls_cache_miss)->Add(1);
  // Let's see if we can transfer something from shared cache.
  auto&& bucket = global->per_node_cache[GetCurrentNodeIndexApprox()];
  auto transferred = bucket.Pop();
  // 如果我们不能
  if (!transferred) {
    (*global->hard_cache_miss)->Add(1);
    (*global->alive_objects)->Add(1);
    return type.create();  // Bad luck.
  }
  auto rc = std::move(transferred->objects.back());
  transferred->objects.pop_back();
  local->objects.refill_from(transferred->objects.data(),
                             transferred->objects.size());
  // Everything here is invalidated. So don't let the destructor to destroy
  // them.
  transferred->objects.clear();
  return rc;
}
```

per_node_cache顾名思义

```cpp
// Global (to all scheduling group) pool descriptor.
struct GlobalPoolDescriptor {
  const TypeDescriptor* type;
  const std::size_t min_blocks_per_node;
  const std::size_t max_blocks_per_node;  // After substracting low water-mark.
  const std::chrono::nanoseconds max_idle;
  const std::size_t transfer_threshold;
  const std::size_t transfer_batch_size;

  std::unique_ptr<Bucket[]> per_node_cache;

  // Below are exported metrics for perf. analysis.

  // Thread-local cache miss.
  std::unique_ptr<ExposedGauge<std::uint64_t>> tls_cache_miss;
  // Miss in all-level cache.
  std::unique_ptr<ExposedGauge<std::uint64_t>> hard_cache_miss;
  // Number of alive objects.
  std::unique_ptr<ExposedGauge<std::int64_t>> alive_objects;
  // Latency of slow path.
  std::unique_ptr<flare::internal::ExposedMetricsInTsc> slow_get_latency,
      slow_put_latency;

  // This is required so as not to define `Bucket` here.
  ~GlobalPoolDescriptor();
};
```

```cpp
std::size_t GetCurrentNodeIndexApprox() {
  FLARE_INTERNAL_TLS_MODEL thread_local std::chrono::steady_clock::time_point
      next_update;
  FLARE_INTERNAL_TLS_MODEL thread_local std::size_t node{};
  if (FLARE_UNLIKELY(next_update < ReadCoarseSteadyClock())) {
    next_update = ReadCoarseSteadyClock() + 1s;
    node = internal::numa::GetCurrentNodeIndex();
  }
  return node;
}
```

这里调用GetCurrentNodeIndex去获取node的index，这里的node是thread_local std::size_t

最终调用的是GetCurrentNodeIndex

```cpp
std::size_t GetCurrentNodeIndex() { return GetNodeIndex(GetCurrentNode()); }
```

```cpp
std::size_t GetNodeIndex(int node_id) {
  FLARE_CHECK_LT(node_id, node_index.size());
  FLARE_CHECK_LT(node_index[node_id], nodes_present.size());
  return node_index[node_id];
}
```

```cpp
int GetCurrentNode() {
  unsigned cpu, node;

  // Another approach: https://stackoverflow.com/a/27450168
  FLARE_CHECK_EQ(0, GetCpu(&cpu, &node, nullptr), "Cannot get NUMA ID.");
  return node;
}
```

至于GetCpu怎么获取信息的，我们这里暂不深究

```cpp
struct alignas(hardware_destructive_interference_size) Bucket {
  // NOT protected by `lock`.
  std::atomic<std::chrono::steady_clock::duration> last_wash{};

  // NOT protected by `lock`.
  //
  // This flag prevents multiple thread from flushing the bucket concurrently,
  // which introduces contention.
  std::atomic<bool> flushing{};

  // Protects both primary & secondary cache.
  Spinlock lock;

  // Object are normally cached here, except for the last `kLowWaterMark`
  // objects.
  //
  // For those "backup" objects, see below.
  flare::internal::DoublyLinkedList<Block, &Block::chain> primary_cache;

  // Life saver.
  //
  // We always keep at most `kLowWaterMark` objects here. Objects kept here are
  // not subject to washout.
  //
  // The reason why we can't keep them in `primary_cache` (see above) as well it
  // that objects in the "secondary" cache are likely to be idle for long. Were
  // they placed in `primary_cache`, they'll likely to be victims of our idle
  // object elimination algorithm.
  flare::internal::DoublyLinkedList<Block, &Block::chain> secondary_cache;

  // Read only.
  std::size_t secondary_cache_size;

  // Grab up an object.
  std::unique_ptr<Block> Pop() noexcept {
    std::scoped_lock _(lock);
    if (auto rc = primary_cache.pop_back()) {
      return std::unique_ptr<Block>(rc);
    }
    if (auto rc = secondary_cache.pop_back()) {
      return std::unique_ptr<Block>(rc);
    }
    return nullptr;
  }

  // Return an object.
  void Push(std::unique_ptr<Block> block) noexcept {
    std::scoped_lock _(lock);
    // It's always returned to the primary cache. Moving it to secondary cache
    // when necessary is done when washing out the primary cache.
    primary_cache.push_back(block.release());
  }

  ~Bucket() {
    while (Pop()) {
      // NOTHING.
    }
    FLARE_CHECK(primary_cache.empty());
    FLARE_CHECK(secondary_cache.empty());
  }
};
```