template <typename... Args>
bool logicalAnd(Args... args) {
    // Binary folding.
    return (true && ... && args);
}

template <typename... Args>
void mycout(Args... args) {
  (std::cout<<...<<args);
}