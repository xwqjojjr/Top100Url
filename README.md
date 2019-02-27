### **题目要求**</br>
100GB url 文件，使用 1GB 内存计算出出现次数 top100 的 url 和出现的次数。</br>
### **整体思路**</br>
采用Top-K问题的常见思路，把大文件转换为小文件再进一步处理。首先采用Hash(Url)%100的方法，把Url分成100小份，如果生成的文件大小仍然大于内存大小，则使用另一种哈希方法继续划分数据。</br>

接着在内存中维护一个大小为100的大根堆遍历小文件，将每个小文件依次加载到内存，使用Map<string,int>获得每个Url在文件中出现的次数，把每个小文件的HashMap放入大根堆中，每次放入都调整堆。
最后堆中所剩就是重复出现次数的Top100。</br>
![image](https://github.com/xwqjojjr/Top100Url/blob/master/Top100Url.png)
### **数据集选择：人造数据和真实数据**</br>
在Github和Kaggle等网站没有找满足要求的真实数据，其中印第安纳大学提供2.5TB的Url点击数据，但需要邮寄一块硬盘并等待印第安纳大学寄回来。综合考虑下，本实验采用人造数据。</br>
### **造数据和划分数据**</br>
使用Python生成数据，数据格式为 xxx.xxx/xxxxx/xxxxx…。一条Url大约40B，则100GB的Url数据共100*1024*1024*1024/40 约27亿条数据。</br>
划分数据也使用Python。</br>
内存占用分析/保证内存小于1G</br>
划分阶段，将数据写入到文件后，及时释放内存。
在读每个小文件并计算Top100阶段，程序每次读入一个文件，同时一致在系统中维护一个大小为100的堆，内存使用不超过题目规定。</br>
### **测试**</br>
使用实验室服务器，
```
CPU Intel(R) Xeon(R) CPU E5-2620 v3 @ 2.40GHz 12核处理器
机械硬盘、64GB内存

```
软件环境为:
```
Ubuntu 16.04.5 LTS
python 2.7.12
g++ (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
```
1. 使用 makeData.py生成数据
```
python makeData.py -f data.txt -s 1
```
2. 使用devideFile.py切分数据
```
python devideFile.py -n 100 -f data.txt
```
3. 编译并运行cpp，其中参数100表示文件数量
```
g++ -o hashMap hashMap.cpp
./hashMap 100
```
### **待解决的问题**</br>
- [ ] 1. 如何证明结果的正确性？</br>
在其他平台上跑，对比结果。
- [ ] 2. 可否使用其他数据结构或架构解决类似的问题？</br>
- [ ] 3. 根据输入的文件大小和系统内存，动态调整切分文件大小和数量</br>
- [ ] 4  还没有跑100G的测试</br>
- [ ] 5. 小数据(5~10GB)测试发现，人造数据过于平均，每个Url出现次数基本相同，Top100中Url的频率基本一致</br>


### **参考文献**</br>
[1] Awesome Public Datasets
https://github.com/awesomedata/awesome-public-datasets</br>
[2]Click Dataset
http://cnets.indiana.edu/groups/nan/webtraffic/click-dataset/</br>
