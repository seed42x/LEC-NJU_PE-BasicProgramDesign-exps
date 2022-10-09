作者：呵呵一笑百媚生
链接：https://www.zhihu.com/question/35359910/answer/64276570
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

# coding:utf8

import sys, tty, termios, os
import urllib2

# 生成文本（单词、句子）列表
def GenWordList():
	data = urllib2.urlopen('http://cn.bing.com/robots.txt').read()
	wordList = list(set(data.split('\r\n')))
	wordList.sort()
	return wordList[1:]	# 去除第一行空白

wordList = GenWordList()

# 根据关键字key获取关联的候选词列表
def getCandidates(key):
	return (word for word in wordList if word.lower().startswith(key.lower()))

# 输入的关键字发生变化时，刷新界面
def onTextChanged(text):
	os.system('clear')
	print text
	print '\n'.join([word for no,word in enumerate(getCandidates(text)) if no < 10])

# 等待键盘按键
def waitForAnyKey():
	fd = sys.stdin.fileno()
	backup = termios.tcgetattr(fd)
	try:
		tty.setraw(fd)
		return ord(sys.stdin.read(1))
	finally:
		termios.tcsetattr(fd, termios.TCSADRAIN, backup)

# 主循环
def eventLoop():
	text = ''
	while True:
		keyCode = waitForAnyKey()		
		if keyCode == 3:	# Ctrl+C退出
			break
		if keyCode == 127:	# Backspace删除一个字符
			if len(text) == 0:
				continue
			text = text[:-1]
			onTextChanged(text)
		elif keyCode >= 32 and keyCode <= 126:	# 可打印字符
			text += chr(keyCode)
			onTextChanged(text)
		

os.system('clear')
eventLoop()