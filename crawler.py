#!/usr/bin/env python
# coding: utf-8

# In[1]:


import requests
from bs4 import BeautifulSoup
import re
import os
from urllib.request import urlretrieve
from shutil import copyfile


# In[2]:


#建立名為"CPE"的資料夾
d_name = os.path.join(os.getcwd(), 'CPE')
if not os.path.exists(d_name):
    os.makedirs(d_name)


# In[3]:


#取得CPE官網的html
r = requests.get("https://cpe.cse.nsysu.edu.tw/history.php")
soup = BeautifulSoup(r.text, "html.parser")
#print(soup.prettify())


# In[4]:


#取得每一次考試紀錄的連結
result = soup.find_all("a")
urls = []
for i in result:
    if i.text == "考試題目":
        urls.append(i.attrs["href"])


# In[5]:


compile_failed = os.system('g++ compare.cpp -o compare.exe')
if not os.path.isfile(os.path.join(os.getcwd(), 'error_report.txt')):
    f = open("error_report.txt", "x")


# In[6]:


if not compile_failed:
    for url in urls:

        test = requests.get(url)
        soups = BeautifulSoup(test.text, "html.parser")

        datas = [soups.find("h3").text] #datas[0]紀錄CPE日期

        #同一題的資料會在同一個tr內
        for j in soups.find_all("tr"):
            question = [None for i in range(6)] #[題目, 題目網址, code網址, 測資A網址, 測資B網址, 考生答對率]
            for idx, k in enumerate(j.find_all("td")):
                for l in k.find_all("a"):
                    if re.compile(r'\d+\:.+').search(l.text) != None:
                        question[0] = re.findall(re.compile(r'\d+\:[^\t\n\r]+[^\s]'), l.text)[0] #題目
                        question[1] = l.attrs["href"] #題目網址
                    elif "pdf" in l.text:
                        question[1] = l.attrs["href"]
                    elif "code" in l.text:
                        question[2] = l.attrs["href"] #code網址
                    elif "測資" in l.text:
                        if question[3] == None:
                            question[3] = l.attrs["href"] #測資A網址
                        else:
                            question[4] = l.attrs["href"] #測資B網址
                if idx == 7:
                    question[5] = k.text #考生答對率
                if idx == 8:
                    question[5] = k.text #考生答對率(2017/05/23有8行)

                if question[1] != None                    and question[1][-3:] != 'pdf'                    and re.findall(re.compile(r'http\:\/\/uva.onlinejudge.org\/external\/.+'), question[1]):
                    question[1] = question[1].replace("http", "https")
                    question[1] = question[1].replace("uva.onlinejudge.org", "onlinejudge.org")
                    ori = "p" + re.findall(re.compile(r'\d+\.html'), question[1])[0]
                    new_ = ori.replace("html", "pdf")
                    question[1] = question[1].replace(re.findall(re.compile(r'\d+\.html'), question[1])[0], new_)

            if question[0] != None and question[1] != None:
                datas.append(question)

        #建立當次考試的資料夾
        directory_name = os.path.join(os.getcwd(), 'CPE', datas[0].replace("/", "_").replace(" ", "_"))
        if not os.path.exists(directory_name):
            os.makedirs(directory_name)
        else:
            continue

        for i in range(1, len(datas)):

            #建立每一題的資料夾
            if datas[i][5] != None:
                directory_name_ = os.path.join(directory_name, '(答對率' + datas[i][5] + ')' +                                                datas[i][0].replace("/", "_").replace(":", "").replace("?", "").replace(" ", "_"))
            else:
                directory_name_ = os.path.join(directory_name,                                                datas[i][0].replace("/", "_").replace(":", "").replace("?", "").replace(" ", "_"))
            if not os.path.exists(directory_name_):
                os.makedirs(directory_name_)
            
            #下載題目
            try:
                if datas[i][1] != None:
                    urlretrieve(datas[i][1], os.path.join(directory_name_,                                 datas[i][0].replace("/", "_").replace(":", "").replace("?", "") + '.pdf'))

            except:
                with open("error_report.txt", "a") as f:
                    f.write('error download question "' + datas[i][0] + '" in ' + datas[0] + '\n')
                    f.write('the url is ' + datas[i][1] + '\n')
                    f.write('in ' + url + '\n')
                    f.write('\n')
#                 print('error download question "' + datas[i][0] + '" in ' + datas[0])
#                 print('the url is ' + datas[i][1])
#                 print('in ' + url)
#                 print()

            #下載code
            try:
                if datas[i][2] != None:
                    write_text = BeautifulSoup(requests.get(datas[i][2]).text, "html.parser").find("pre").contents[0]
                    while write_text[0] == '\n' or write_text[0] == '\r':
                        write_text = write_text[1:]
                    while write_text[-1] == '\n' or write_text[-1] == '\r':
                        write_text = write_text[:-1]
                    with open(os.path.join(directory_name_, 'ref_code.cpp'), 'w', encoding="utf-8", newline='') as f:
                        f.write(write_text)
            except:
                with open("error_report.txt", "a") as f:
                    f.write('error download code of "' + datas[i][0] + '" in ' + datas[0] + '\n')
                    f.write('the url is ' + datas[i][2] + '\n')
                    f.write('in ' + url + '\n')
                    f.write('\n')
#                 print('error download code of "' + datas[i][0] + '" in ' + datas[0])
#                 print('the url is ' + datas[i][2])
#                 print('in ' + url)
#                 print()

            #下載測資A/測資
            try:
                if datas[i][3] != None:
                    write_text = BeautifulSoup(requests.get(datas[i][3]).text, "html.parser").find_all("pre")[0].contents[0]
                    while write_text[0] == '\n' or write_text[0] == '\r':
                        write_text = write_text[1:]
                    while write_text[-1] == '\n' or write_text[-1] == '\r':
                        write_text = write_text[:-1]
                    with open(os.path.join(directory_name_, 'test1.in'), 'w', encoding="utf-8", newline='') as f:
                        f.write(write_text)

                    write_text = BeautifulSoup(requests.get(datas[i][3]).text, "html.parser").find_all("pre")[1].contents[0]
                    while write_text[0] == '\n' or write_text[0] == '\r':
                        write_text = write_text[1:]
                    while write_text[-1] == '\n' or write_text[-1] == '\r':
                        write_text = write_text[:-1]
                    with open(os.path.join(directory_name_, 'test1.out'), 'w', encoding="utf-8", newline='') as f:
                        f.write(write_text)    
            except:
                with open("error_report.txt", "a") as f:
                    f.write('error download test data of "' + datas[i][0] + '" in ' + datas[0] + '\n')
                    f.write('the url is ' + datas[i][3] + '\n')
                    f.write('in ' + url + '\n')
                    f.write('\n')
#                 print('error download test data of "' + datas[i][0] + '" in ' + datas[0])
#                 print('the url is ' + datas[i][3])
#                 print('in ' + url)
#                 print()

            #下載測資B
            try:
                if datas[i][4] != None:
                    write_text = BeautifulSoup(requests.get(datas[i][4]).text, "html.parser").find_all("pre")[0].contents[0]
                    while write_text[0] == '\n' or write_text[0] == '\r':
                        write_text = write_text[1:]
                    while write_text[-1] == '\n' or write_text[-1] == '\r':
                        write_text = write_text[:-1]
                    with open(os.path.join(directory_name_, 'test2.in'), 'w', encoding="utf-8", newline='') as f:
                        f.write(write_text)

                    write_text = BeautifulSoup(requests.get(datas[i][4]).text, "html.parser").find_all("pre")[1].contents[0]
                    while write_text[0] == '\n' or write_text[0] == '\r':
                        write_text = write_text[1:]
                    while write_text[-1] == '\n' or write_text[-1] == '\r':
                        write_text = write_text[:-1]
                    with open(os.path.join(directory_name_, 'test2.out'), 'w', encoding="utf-8", newline='') as f:
                        f.write(write_text)
            except:
                with open("error_report.txt", "a") as f:
                    f.write('error download test data of "' + datas[i][0] + '" in ' + datas[0] + '\n')
                    f.write('the url is ' + datas[i][4] + '\n')
                    f.write('in ' + url + '\n')
                    f.write('\n')
#                 print('error download test data of "' + datas[i][0] + '" in ' + datas[0])
#                 print('the url is ' + datas[i][4])
#                 print('in ' + url)
#                 print()

            # 核對程式
            copyfile(os.path.join(os.getcwd(), 'compare.exe'), os.path.join(directory_name_, 'compare.exe'))

else:
    print("compile failed!")


# In[ ]:




