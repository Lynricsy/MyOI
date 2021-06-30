import requests
import os

print("downloading Skins&Characters")
url = 'https://www.luogu.com.cn/api/verify/captcha'
r = requests.get(url)
with open("cap.jpg", "wb") as code:
     code.write(r.content)
print("Successfully updated.Enjoy!")