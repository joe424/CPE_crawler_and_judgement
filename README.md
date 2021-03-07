# CPE_crawler_and_judgement


(目前只能用在windows)
<br/>

安裝第三方模組:
```
pip install -r requirements.txt
```
<br/>

使用 `crawler.py` 來爬取CPE題目:
> 若有新考題且要爬取也可使用此指令
```
python crawler.py
```
<br/>

若 `compare.cpp` 有更新且要加入到所有考題的資料夾內:
```
python upgrade.py
```

將寫好的程式碼(ex:ans.cpp)判斷是否正確
```
compare.exe ans.cpp
```