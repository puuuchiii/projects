# 从 requests_html 库中导入 HTMLSession 类,并创建一个 HTMLSession 类的实例
from requests_html import HTMLSession
session = HTMLSession()

# 定义要访问的 API 地址
url = 'https://api.blockcypher.com/v1/btc/test3/addrs/n1XuzfuSNJ8Ea21jumJG381mc6be9oGJf5/full?limit=50'

# 使用 HTMLSession 发送一个 GET 请求到指定的 URL，并获取响应数据
response = session.get(url)

# 将响应的 HTML 内容的全部文本写入到文件中
with open("tx.txt", "w") as f:    
    f.write(response.html.full_text)
