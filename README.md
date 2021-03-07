# CPE_crawler_and_judgement

<div class="panel panel-warning">
**Warning**
{: .panel-heading}
<div class="panel-body">
目前只能用在windows
</div>
</div>

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

若要 `compare.exe` 有更新且要加入到所有考題的資料夾內:
```
python upgrade.py
```