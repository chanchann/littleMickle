import json

def read_and_filter_data(file_path, filter_condition):
    # 初始化一个空列表来存储满足条件的symbols
    filtered_symbols = []

    # 读取文件内容
    with open(file_path, 'r') as file:
        # 假设文件内容是JSON格式的
        data = json.load(file)
    # print(data["symbols"])
    data1 = data.get("symbols")
    print(len(data1))
    data2 = data.get("assets")
    print(data2)
    # print(data["timezone"])
    filtered_symbols = filter_condition(data)
    # 遍历数据并应用过滤条件
    # for item in data:
    #     if filter_condition(item):
    #         # 如果item满足过滤条件，将其symbol添加到列表中
    #         filtered_symbols.append(item['symbol'])
    print(len(filtered_symbols))
    return filtered_symbols

# 定义过滤条件
def filter(json_data):
    
    return [
        symbol['symbol'] for symbol in json_data.get('symbols', [])
        if symbol.get('contractType') == 'PERPETUAL'
        and symbol.get('quoteAsset', '').lower() == 'usdt'
        and symbol.get('status') == 'TRADING'
    ]

# 使用函数
file_path = '../data/output.txt'
result = read_and_filter_data(file_path, filter)

# 打印结果
print("Filtered symbols:", result)