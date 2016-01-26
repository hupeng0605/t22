/**************************************************************************/
/*
FILE        : KCStringIDDef.h

*/
/**************************************************************************/


#pragma once

// /************************************************************************/
// /* 天派F8D和A9的语言ID定义                                              */
// /************************************************************************/
// 
// #define     HMI_LANG_TX_NULL        0
// #define     HMI_LANG_TX_AM          1   // 上午
// #define     HMI_LANG_TX_PM          2   // 下午
// #define     HMI_LANG_TX_SUNDAY      3   // 星期天
// #define     HMI_LANG_TX_MONDAY      4   // 星期一
// #define     HMI_LANG_TX_TUESDAY     5   // 星期二
// #define     HMI_LANG_TX_WEDNESDAY   6   // 星期三
// #define     HMI_LANG_TX_THURSDAY    7   // 星期四
// #define     HMI_LANG_TX_FRIDAY      8   // 星期五
// #define     HMI_LANG_TX_SATURDAY    9   // 星期六
// 
// // ******************************************天气相关言语ID
// #define     HMI_LANG_TX_LASTUPDATE 10 // 上次更新：%d%s前 更新：
// #define     HMI_LANG_TX_3G 11 // 3G网络
// #define     HMI_LANG_TX_MUSICSEARCH 12 // 音乐搜索
// #define     HMI_LANG_TX_WEATHER 13 // 天气
// #define     HMI_LANG_TX_RSS 14 // 新闻
// #define     HMI_LANG_TX_INTERNETRADIO 15 // 网络收音机
// #define     HMI_LANG_TX_CHANGEBK      16 // 切换风格
// #define     HMI_LANG_TX_TIMEFORMAT    17// 时间格式
// 
// // ******************************************主界面相关的语言ID
// #define     HMI_LANG_TX_MAINMENU    18 //主菜单
// #define     HMI_LANG_TX_MUSIC       19 //音乐
// #define     HMI_LANG_TX_VIDEO   20  //视频
// #define     HMI_LANG_TX_SET     21  //设置
// #define     HMI_LANG_TX_PICTUREVIEW 22 // 图片浏览
// #define     HMI_LANG_TX_RADIO   23 //收音机
// #define     HMI_LANG_TX_NAVI    24 //导航
// #define     HMI_LANG_TX_NET     25 //网络
// #define     HMI_LANG_TX_BLUET   26 //蓝牙
// #define     HMI_LANG_TX_PICTURE 27 //图片
// #define     HMI_LANG_TX_OK      28 //确定
// #define     HMI_LANG_TX_CANCEL  29 //取消
// #define     HMI_LANG_TX_HDD  30 //硬盘
// #define     HMI_LANG_TX_USB  31 // U盘
// #define     HMI_LANG_TX_SD   32 // SD卡
// #define     HMI_LANG_TX_IPOD  33 // iPod
// #define     HMI_LANG_TX_CD    34 // CD
// #define     HMI_LANG_TX_SAT   35 // 卫星收音机
// #define     HMI_LANG_TX_TV   36 // TV
// #define     HMI_LANG_TX_DVD  37 // DVD
// #define     HMI_LANG_TX_AV1  38 // AV1
// #define     HMI_LANG_TX_AV2  39 // AV2
// #define     HMI_LANG_TX_CAMERA  40 // 后视镜
// #define     HMI_LANG_TX_COMSETTING     41 // 通用设置
// #define     HMI_LANG_TX_VEDIOSETTING  42 // 视频设置
// #define     HMI_LANG_TX_MUSICSETTING  43 // 音频设置
// #define     HMI_LANG_TX_NETSETTING    44 // 网络设置
// #define     HMI_LANG_TX_OTHERSETTING  45 // 其他设置
// #define     HMI_LANG_TX_REAR          46 // 后台
// #define     HMI_LANG_TX_DATEANDTIME   47 // 日期和时间
// #define     HMI_LANG_TX_BACKLIGHT     48 // 背光强度
// #define     HMI_LANG_TX_SCREENSAVE    49 // 屏保
// #define     HMI_LANG_TX_STYLE         50 // 风格设置
// #define     HMI_LANG_TX_MUSICHDD      51 // 音乐 | 硬盘
// #define     HMI_LANG_TX_MUSICUSB      52 // 音乐 | U盘
// #define     HMI_LANG_TX_MUSICSD       53 // 音乐 | SD卡
// #define     HMI_LANG_TX_MUSICIPOD   54 // 音乐 | iPod
// #define     HMI_LANG_TX_MUSICCD     55 // 音乐 | CD
// #define     HMI_LANG_TX_VEDIOHDD    56 // 视频 | 硬盘
// #define     HMI_LANG_TX_VEDIOUSB    57 // 视频 | U盘
// #define     HMI_LANG_TX_VEDIOSD     58 // 视频 | SD卡
// #define     HMI_LANG_TX_VEDIOIPOD   59 // 视频 | iPod
// #define     HMI_LANG_TX_VEDIODVD    60 // 视频 | DVD
// #define     HMI_LANG_TX_VEDIOAV1    61 // 视频 | AV1
// #define     HMI_LANG_TX_VEDIOAV2    62 // 视频 | AV2
// #define     HMI_LANG_TX_VEDIOCAMERA 63 // 视频 | 后视镜
// #define     HMI_LANG_TX_MODEM       64 // 拨号上网
// #define     HMI_LANG_TX_CALLCENTER  65 // 连接Call Center
// #define     HMI_LANG_TX_MESSAGE     66 // 短信息
// #define     HMI_LANG_TX_CONNECTING  67 // 正在拨号...
// #define     HMI_LANG_TX_SUCCEED     68 // 连接成功,连接速率%d%s.
// #define     HMI_LANG_TX_DISCONNECT  69 // 已断开连接
// #define     HMI_LANG_TX_CUTCONNECT  70 // 断开连接
// #define     HMI_LANG_TX_EQ  71 // 均衡器
// #define     HMI_LANG_TX_BASE    72 // 低  音
// #define     HMI_LANG_TX_TREBLE  73 // 高  音
// #define     HMI_LANG_TX_BALANCE 74 // 平  衡
// #define     HMI_LANG_TX_FALLOFF 75 // 衰  减
// #define     HMI_LANG_TX_XBSBASE 76 // 重低音
// #define     HMI_LANG_TX_TYPE    77 // 类  型
// #define     HMI_LANG_TX_LOUDNESS    78 // 响  度
// #define     HMI_LANG_TX_POP 79 // 流  行
// #define     HMI_LANG_TX_DJ  80 // 摇  滚
// #define     HMI_LANG_TX_CLASSICAL   81 // 古  典
// #define     HMI_LANG_TX_OPERA   82 // 歌  剧
// #define     HMI_LANG_TX_DANCE   83 // 舞  曲
// #define     HMI_LANG_TX_KNIGHT  84 // 爵  士
// #define     HMI_LANG_TX_MUSICPLAYLIST 85 //播放列表
// #define     HMI_LANG_TX_MUSICARTIST 86  // 艺术家
// #define     HMI_LANG_TX_MUSICSPECIAL 87 // 专辑
// #define     HMI_LANG_TX_MUSICSONG   88 //歌曲
// #define     HMI_LANG_TX_MUSICLOOKUP 89 //查找
// #define     HMI_LANG_TX_MUSICRECENTPLAY 90 //最近播放的歌曲列表
// #define     HMI_LANG_TX_MUSICRECENTADD  91 //最近添加歌曲列表
// #define     HMI_LANG_TX_MUSICOFFENPLAY  92 //最常播放的50首歌曲
// #define     HMI_LANG_TX_BLUE 93 // 天空蓝
// #define     HMI_LANG_TX_PURPLE 94 // 梦幻紫
// #define     HMI_LANG_TX_ORANGE 95 // 阳光橙
// #define     HMI_LANG_TX_GLOWWORM 96 // 萤火虫
// #define     HMI_LANG_TX_AURORA 97 // 北极光
// #define     HMI_LANG_TX_RED 98 // 都市红
// #define     HMI_LANG_TX_SHADOW 99 // 光影
// #define     HMI_LANG_TX_AURORA_ 100 // 北极光
// #define     HMI_LANG_TX_RED_ 101 // 都市红
// #define     HMI_LANG_TX_SHADOW_ 102 // 光影
// #define     HMI_LANG_TX_TIME  103  //当前时间
// #define     HMI_LANG_TX_TIMEFORMAT_SET 104  //时间格式
// #define     HMI_LANG_TX_HOUR12     105 //12小时制
// #define     HMI_LANG_TX_HOUR24    106 //24小时制
// #define     HMI_LANG_TX_LANGSWITCH  107 //言语切换
// #define     HMI_LANG_TX_DIGITALCLOCK  108 //数字时钟
// #define     HMI_LANG_TX_ANALOGCLOCK   109 //模拟时钟
// #define     HMI_LANG_TX_CHINESE       110 //中文
// #define     HMI_LANG_TX_ENGLISH       111//英文
// #define     HMI_LANG_TX_ON       112 // 开(ON)
// #define     HMI_LANG_TX_OFF       113// 关(OFF)
// #define     HMI_LANG_TX_DELETE    114 //删除
// #define     HMI_LANG_TX_ADD    115//收藏
// 
// // ******************************************网络收音机相关言语ID
// #define     HMI_LANG_TX_STOPPED    116//播放停止
// #define     HMI_LANG_TX_PLAYING    117//正在播放
// #define     HMI_LANG_TX_SCANFORWARD    118//向前搜索
// #define     HMI_LANG_TX_SCANREVERSE    119//向后搜索
// #define     HMI_LANG_TX_BUFFERING    120//正在缓冲
// #define     HMI_LANG_TX_WAITING    121//正在等待流开始
// #define     HMI_LANG_TX_MEDIAENDED    122//播放流已结束
// #define     HMI_LANG_TX_TRANSITIONING    123//准备新的媒体文件
// #define     HMI_LANG_TX_READY    124//播放准备就绪
// #define     HMI_LANG_TX_RECONNECTING    125//尝试重新连接流媒体数据
// 
// #define     HMI_LANG_TX_LASTUPDATE_DAY    126//上次更新：%d天前 更新
// #define     HMI_LANG_TX_LASTUPDATE_HOUR    127//上次更新：%d小时前 更新
// #define     HMI_LANG_TX_LASTUPDATE_MINUTE    128//上次更新：%d分钟前 更新
// #define     HMI_LANG_TX_DATESETTING           129  //日期设置
// #define     HMI_LANG_TX_ASPECT                130//宽高比
// #define     HMI_LANG_TX_AUXIN                 131//AUXIN   
// #define     HMI_LANG_TX_BRIGHTNESS            132 //亮度设置
// #define     HMI_LANG_TX_MONITOROFF            133//MonitorOff
// #define     HMI_LANG_TX_BASSFREQUENCY         134//低音频率
// #define     HMI_LANG_TX_TREBLEFREQUENCY       135//高音频率
// #define     HMI_LANG_TX_BASSCUTOFFRATE        136//重低音截止率
// #define     HMI_LANG_TX_Q_BASS                 137//重低音Q 值 
// #define     HMI_LANG_TX_FRONTSPEAKERS         138//Front Speakers
// #define     HMI_LANG_TX_CENTERSPEAKERS        139//CENTERSPEAKERS
// #define     HMI_LANG_TX_SUNWOOFER             140//SUNWOOFER
// #define     HMI_LANG_TX_CENTERDELAY           141//CENTERDELAY
// #define     HMI_LANG_TX_DOWNSAMPLIN           142//DOWNSAMPLIN
// #define     HMI_LANG_TX_SURRDELAY             143//SURRDELAY
// #define     HMI_LANG_TX_VOLUME                144//VOLUME
// #define     HMI_LANG_TX_TOUCHREVISE           145//触摸校准
// #define     HMI_LANG_TX_LANGUAGE              146//多语言设置
// #define     HMI_LANG_TX_AGECONTROL            147//年龄控制
// #define     HMI_LANG_TX_MASTERRESET           148//出厂设置
// #define     HMI_LANG_TX_PARENTALCONTROL       149//Parental Control
// #define     HMI_LANG_TX_ANTICODE              150//ANTICODE
// #define     HMI_LANG_TX_ANTITHEFTSW           151//ANTITHEFTSW
// #define     HMI_LANG_TX_SOFEWWAREUPDATE       152//Software Update
// #define     HMI_LANG_TX_NAVIUPDATE            153//Navi Update
// #define     HMI_LANG_TX_BTPHONE               154// 电话
// #define     HMI_LANG_TX_BTMUSIC               155// 音乐
// #define     HMI_LANG_TX_BTDEVICE              156// 设备管理
// #define     HMI_LANG_TX_BTSETTING             157// 设置
// #define     HMI_LANG_TX_TIMESETTING           158// 时间设置
// #define     HMI_LANG_TX_PICTUREHDD            159// 图片浏览 | HDD
// #define     HMI_LANG_TX_PICTURESD             160// 图片浏览 | SD
// #define     HMI_LANG_TX_PICTUREUSB            161// 图片浏览 | USB
// #define     HMI_LANG_TX_INTERNETRADIOSETTING  162// 网络收音机设置 
// #define     HMI_LANG_TX_RSSSETTING            163// RSS设置
// #define     HMI_LANG_TX_WEAFORECAST           164//天气预报设置
// #define     HMI_LANG_TX_CODESETTING           165//密码设置  
// #define     HMI_LANG_TX_AUTO                  166//自动
// #define     HMI_LANG_TX_AUTOLISTENING          167//自动收听
// #define     HMI_LANG_TX_BACKGROUNDPLAY        168//后台播发
// #define     HMI_LANG_TX_AUTOUPDATE            169//自动升级
// #define     HMI_LANG_TX_AUTOUPDATESETTING     170//自动更新设置
// #define     HMI_LANG_TX_UNITSETTING           171//单位设置
// #define     HMI_LANG_TX_MANAUL                174//手动
// #define     HMI_LANG_TX_UC                    175//儿童级
// #define     HMI_LANG_TX_MXP                   176//成人级
// #define		HMI_LANG_TX_BTDIAL				  177//拨号
// #define		HMI_LANG_TX_BTHISTORY			  178//通话讯录
// #define		HMI_LANG_TX_BTCONTACT			  179//通讯录
// #define		HMI_LANG_TX_BTMUSICON			  180//蓝牙音乐开
// #define		HMI_LANG_TX_BTMUSICOFF			  181//蓝牙音乐关
// #define		HMI_LANG_TX_BTHANDSET			  182//切换音源
// #define		HMI_LANG_TX_BTSHOWDEVICE		  183//显示/隐藏设备
// #define		HMI_LANG_TX_BTDEVICENAME		  184//设备名
// #define		HMI_LANG_TX_BTDEVICEPWD			  185//设备密码
// #define		HMI_LANG_TX_BTDEVICEADDR		  186//设备地址
// #define		HMI_LANG_TX_BTVERSION			  187//蓝牙版本
// #define		HMI_LANG_TX_BTFINDDEVICE		  188//设备匹配
// #define		HMI_LANG_TX_BTADDDEVICE			  189//添加
// #define		HMI_LANG_TX_BTDELDEVICE			  190//删除
// #define		HMI_LANG_TX_BTDELALLDEVICE		  191//删除所有
// #define		HMI_LANG_TX_BTCNTDEVICE			  192//连接
// #define		HMI_LANG_TX_VEDIOTV				  193//数字电视














/************************************************************************/
/* 歌乐项目的语言ID定义                                                 */
/************************************************************************/
#define     HMI_LANG_CLARION_NULL        	0
#define     HMI_LANG_CLARION_ON			 	1
#define     HMI_LANG_CLARION_OFF		 	2
#define		HMI_LANG_CLARION_General	 	3
#define		HMI_LANG_CLARION_Video		 	4
#define		HMI_LANG_CLARION_Audio		 	5
#define		HMI_LANG_CLARION_Navigation	 	6
#define		HMI_LANG_CLARION_Others		 	7
#define		HMI_LANG_CLARION_DVDWSM		 	8
#define		HMI_LANG_CLARION_Brightness	 	9
#define		HMI_LANG_CLARION_ZERO		 	10
#define     HMI_LANG_CLARION_TITLE       	11
#define     HMI_LANG_CLARION_ARTIST      	12
#define     HMI_LANG_CLARION_ALBUM		 	13
#define     HMI_LANG_CLARION_GENRE		 	14
#define		HMI_LANG_CLARION_RELEASE     	15
#define     HMI_LANG_CLARION_PLAYING     	16
#define     HMI_LANG_CLARION_PAUSE       	17
#define		HMI_LANG_CLARION_REPEATONE   	18
#define		HMI_LANG_CLARION_REPEATALL   	19
#define		HMI_LANG_CLARION_REPEATOFF   	20
#define		HMI_LANG_CLARION_SHUFFLESONG 	21
#define		HMI_LANG_CLARION_SHUFFLEOFF  	22
#define		HMI_LANG_CLARION_STOP        	23
#define		HMI_LANG_CLARION_FF			 	24
#define		HMI_LANG_CLARION_FB			 	25
#define		HMI_LANG_CLARION_AM			 	26
#define		HMI_LANG_CLARION_PM			 	27
#define		HMI_LANG_CLARION_SUNDAY		 	28
#define		HMI_LANG_CLARION_OK			 	29
#define		HMI_LANG_CLARION_CANCEL		 	30
#define     HMI_LANG_CLARION_12HR		 	31
#define     HMI_LANG_CLARION_24HR		 	32
#define		HMI_LANG_CLARION_LOW		 	33
#define		HMI_LANG_CLARION_MIDDLE		 	34
#define		HMI_LANG_CLARION_HIGH		 	35
#define		HMI_LANG_CLARION_AUTO		 	36
#define		HMI_LANG_CLARION_DAY		 	37
#define		HMI_LANG_CLARION_NIGHT		 	38
#define		HMI_LANG_CLARION_LEFT		 	39
#define		HMI_LANG_CLARION_RIGHT		 	40
#define		HMI_LANG_CLARION_NTSC		 	41
#define		HMI_LANG_CLARION_PAL		 	42
#define		HMI_LANG_CLARION_L1			 	43
#define		HMI_LANG_CLARION_L2			 	44
#define		HMI_LANG_CLARION_L3			 	45
#define		HMI_LANG_CLARION_L4			 	46
#define		HMI_LANG_CLARION_L5			 	47
#define		HMI_LANG_CLARION_L6			 	48
#define		HMI_LANG_CLARION_L7			 	49
#define		HMI_LANG_CLARION_L8			 	50
#define		HMI_LANG_CLARION_L9			 	51
#define		HMI_LANG_CLARION_R1			 	52
#define		HMI_LANG_CLARION_R2			 	53
#define		HMI_LANG_CLARION_R3			 	54
#define		HMI_LANG_CLARION_R4			 	55
#define		HMI_LANG_CLARION_R5			 	56
#define		HMI_LANG_CLARION_R6			 	57
#define		HMI_LANG_CLARION_R7			 	58
#define		HMI_LANG_CLARION_R8			 	59
#define		HMI_LANG_CLARION_R9			 	60
#define		HMI_LANG_CLARION_F1			 	61
#define		HMI_LANG_CLARION_F2			 	62
#define		HMI_LANG_CLARION_F3			 	63
#define		HMI_LANG_CLARION_F4			 	64
#define		HMI_LANG_CLARION_F5			 	65
#define		HMI_LANG_CLARION_F6			 	66
#define		HMI_LANG_CLARION_F7			 	67
#define		HMI_LANG_CLARION_F8			 	68
#define		HMI_LANG_CLARION_F9			 	69
#define		HMI_LANG_CLARION_BASSBOOST	 	70
#define		HMI_LANG_CLARION_IMPACT		 	71
#define		HMI_LANG_CLARION_EXCITE		 	72
#define		HMI_LANG_CLARION_CUSTOM		 	73
#define		HMI_LANG_CLARION_NORMAL		 	74
#define		HMI_LANG_CLARION_REVERSE	 	75
#define		HMI_LANG_CLARION_THROUGH	 	76
#define		HMI_LANG_CLARION_55HZ		 	77
#define		HMI_LANG_CLARION_85HZ		 	78
#define		HMI_LANG_CLARION_120HZ		 	79
#define		HMI_LANG_CLARION_62HZ		 	80
#define		HMI_LANG_CLARION_95HZ		 	81
#define		HMI_LANG_CLARION_135HZ		 	82
#define		HMI_LANG_CLARION_1			 	83
#define		HMI_LANG_CLARION_2			 	84
#define		HMI_LANG_CLARION_3			 	85
#define		HMI_LANG_CLARION_4			 	86
#define		HMI_LANG_CLARION_5			 	87
#define		HMI_LANG_CLARION_6			 	88
#define		HMI_LANG_CLARION_7			 	89
#define		HMI_LANG_CLARION_8			 	90
#define		HMI_LANG_CLARION_9			 	91
#define		HMI_LANG_CLARION_10			 	92
#define		HMI_LANG_CLARION_11			 	93
#define		HMI_LANG_CLARION_12			 	94
#define		HMI_LANG_CLARION_13			 	95
#define		HMI_LANG_CLARION_14			 	96
#define		HMI_LANG_CLARION_15			 	97
#define		HMI_LANG_CLARION_16			 	98
#define		HMI_LANG_CLARION_17			 	99
#define		HMI_LANG_CLARION_18			 	100
#define		HMI_LANG_CLARION_19			 	101
#define		HMI_LANG_CLARION_20			 	102
#define		HMI_LANG_CLARION_21			 	103
#define		HMI_LANG_CLARION_22			 	104
#define		HMI_LANG_CLARION_23			 	105
#define		HMI_LANG_CLARION_24			 	106
#define		HMI_LANG_CLARION_25			 	107
#define		HMI_LANG_CLARION_26			 	108	
#define		HMI_LANG_CLARION_27			 	109
#define		HMI_LANG_CLARION_28			 	110
#define		HMI_LANG_CLARION_29			 	111
#define		HMI_LANG_CLARION_NEG1		 	112
#define		HMI_LANG_CLARION_NEG2		 	113
#define		HMI_LANG_CLARION_NEG3		 	114
#define		HMI_LANG_CLARION_NEG4		 	115
#define		HMI_LANG_CLARION_NEG5		 	116
#define		HMI_LANG_CLARION_NEG6		 	117
#define		HMI_LANG_CLARION_NEG7		 	118
#define		HMI_LANG_CLARION_KIDSAFE	 	119
#define		HMI_LANG_CLARION_G			 	120
#define		HMI_LANG_CLARION_PG			 	121
#define		HMI_LANG_CLARION_PG13		 	122
#define		HMI_LANG_CLARION_PGR		 	123
#define		HMI_LANG_CLARION_R			 	124
#define		HMI_LANG_CLARION_NC17		 	125
#define		HMI_LANG_CLARION_ADULT		 	126
#define		HMI_LANG_CLARION_ENGLISH	 	127
#define		HMI_LANG_CLARION_DEUTSCH	 	128
#define		HMI_LANG_CLARION_FRANCAIS	 	129
#define		HMI_LANG_CLARION_ITALIANO	 	130
#define		HMI_LANG_CLARION_ESPANOI	 	131
#define		HMI_LANG_CLARION_SVENSKA	 	132
#define		HMI_LANG_CLARION_NEDERLANDS	 	133
#define		HMI_LANG_CLARION_POLISH		 	134
#define		HMI_LANG_CLARION_GREEK		 	135
#define		HMI_LANG_CLARION_RUSSIA		 	136
#define		HMI_LANG_CLARION_PORTUGUES	 	137
#define		HMI_LANG_CLARION_DANSK		 	138
#define		HMI_LANG_CLARION_CHINESE	 	139
#define		HMI_LANG_CLARION_YES		 	140
#define		HMI_LANG_CLARION_NO			 	141
#define		HMI_LANG_CLARION_IGNORE		 	142
#define		HMI_LANG_CLARION_LEVEL		 	143	
#define		HMI_LANG_CLARION_SEQ		 	144
#define		HMI_LANG_CLARION_POPUP		 	145
#define		HMI_LANG_CLARION_SYNC		 	146
#define		HMI_LANG_CLARION_CLOCK		 	147
#define		HMI_LANG_CLARION_AMPM		 	148
#define		HMI_LANG_CLARION_CLOCKMODE	 	149
#define		HMI_LANG_CLARION_BEEP		 	150
#define		HMI_LANG_CLARION_BLUETOOTH	 	151
#define		HMI_LANG_CLARION_WALLPAPER	 	152
#define		HMI_LANG_CLARION_Auxin		 	153
#define		HMI_LANG_CLARION_DIVX		 	154
#define		HMI_LANG_CLARION_DIMMER		 	155
#define		HMI_LANG_CLARION_TEL		 	156
#define		HMI_LANG_CLARION_TFT		 	157
#define		HMI_LANG_CLARION_CAMERAINPUT 	158
#define		HMI_LANG_CLARION_VERSION	 	159
#define		HMI_LANG_CLARION_DVD		 	160
#define		HMI_LANG_CLARION_BRIGHTNESS	 	161
#define		HMI_LANG_CLARION_BALANCE	 	162
#define		HMI_LANG_CLARION_FADER		 	163
#define		HMI_LANG_CLARION_SELECTEQ	 	164
#define		HMI_LANG_CLARION_SUBCTRL	 	165
#define		HMI_LANG_CLARION_SUBPHASE	 	166
#define		HMI_LANG_CLARION_HIGHFILTER	 	167
#define		HMI_LANG_CLARION_LOWFILTER	 	168
#define		HMI_LANG_CLARION_AMP		 	169
#define		HMI_LANG_CLARION_MAGNA		 	170
#define		HMI_LANG_CLARION_TUNERGAIN		171
#define		HMI_LANG_CLARION_DISC		 	172
#define		HMI_LANG_CLARION_USB		 	173
#define		HMI_LANG_CLARION_AUX		 	174
#define		HMI_LANG_CLARION_HD			 	175
#define		HMI_LANG_CLARION_SIRIUS		 	176
#define		HMI_LANG_CLARION_DVBTGAIN	 	177
#define		HMI_LANG_CLARION_GPSTIME	 	178
#define		HMI_LANG_CLARION_NAVIINTERRUPT	179
#define		HMI_LANG_CLARION_VOICE		 	180
#define		HMI_LANG_CLARION_PASSWORD	 	181
#define		HMI_LANG_CLARION_PARCTROL	 	182
#define		HMI_LANG_CLARION_AUDIOLAN	 	183
#define		HMI_LANG_CLARION_SUBLAN		 	184
#define		HMI_LANG_CLARION_CHANGELAN	 	185
#define		HMI_LANG_CLARION_BLINK		 	186
#define		HMI_LANG_CLARION_TS			 	187
#define		HMI_LANG_CLARION_LOADFAC	 	188
#define		HMI_LANG_CLARION_DVDREGION	 	189
#define		HMI_LANG_CLARION_PARKING	 	190
#define		HMI_LANG_CLARION_MACRO		 	191
#define		HMI_LANG_CLARION_SUPERRESET	 	192
#define		HMI_LANG_CLARION_DEFAULT	 	193
#define		HMI_LANG_CLARION_MODE1		 	194
#define		HMI_LANG_CLARION_LOCKED		 	195
#define		HMI_LANG_CLARION_PTYLAN		 	196
#define		HMI_LANG_CLARION_PARENTSETTING	197
#define		HMI_LANG_CLARION_NOTHING	 	198
#define		HMI_LANG_CLARION_CLEAR		 	199
#define		HMI_LANG_CLARION_CODE		 	200
#define		HMI_LANG_CLARION_OLDCODE	 	201
#define		HMI_LANG_CLARION_NEWCODE	 	202
#define		HMI_LANG_CLARION_RECODE	     	203
#define		HMI_LANG_CLARION_TA		     	204
#define		HMI_LANG_CLARION_AF			 	205	
#define		HMI_LANG_CLARION_REG		 	206
#define		HMI_LANG_CLARION_MODE		 	207
#define		HMI_LANG_CLARION_PTY		 	208
#define		HMI_LANG_CLARION_DX			 	209
#define		HMI_LANG_CLARION_LOCAL		 	210
#define		HMI_LANG_CLARION_SEEK		 	211
#define		HMI_LANG_CLARION_START		 	212
#define		HMI_LANG_CLARION_AS			 	213
#define		HMI_LANG_CLARION_TEXT		 	214
#define		HMI_LANG_CLARION_PS			 	215
#define		HMI_LANG_CLARION_PRESETSCAN	 	216
#define		HMI_LANG_CLARION_DIRECT		 	217
#define		HMI_LANG_CLARION_PRESET		 	218
#define		HMI_LANG_CLARION_GAIN		 	219
#define		HMI_LANG_CLARION_FREQUENCY		220
#define		HMI_LANG_CLARION_Q				221
#define		HMI_LANG_CLARION_BASS			222
#define		HMI_LANG_CLARION_MID			223
#define		HMI_LANG_CLARION_TREBLE			224
#define		HMI_LANG_CLARION_CONNECT		225
#define		HMI_LANG_CLARION_CODENOMATCH	226
#define		HMI_LANG_CLARION_CODEBESET		227
#define		HMI_LANG_CLARION_CODEERASED		228
//#define		HMI_LANG_CLARION_CODEINCORRECT	229
#define		HMI_LANG_CLARION_CODEERROR		230
#define		HMI_LANG_CLARION_PASSWORDSUC	231
#define		HMI_LANG_CLARION_ENTERSYS		232
#define		HMI_LANG_CLARION_DELETE			233
//#define		HMI_LANG_CLARION_ERASECODE		234
#define		HMI_LANG_CLARION_ANTITHEFTSETTING		235
//#define		HMI_LANG_CLARION_SETCODE		236
#define		HMI_LANG_CLARION_RETRY			237
#define		HMI_LANG_CLARION_BACK			238
#define		HMI_LANG_CLARION_PLAY			239
#define		HMI_LANG_CLARION_ONETRACKREPEAT	240
#define		HMI_LANG_CLARION_FLODERREPEAT	241
//#define		HMI_LANG_CLARION_VIDEOSCAN		242
#define		HMI_LANG_CLARION_SCAN			243
#define		HMI_LANG_CLARION_TRADITION		244
#define		HMI_LANG_CLARION_NODEVICE		245
#define		HMI_LANG_CLARION_DEVICE			246
#define		HMI_LANG_CLARION_PINCODE		247
#define		HMI_LANG_CLARION_AUTOCONNECT	248
#define		HMI_LANG_CLARION_AUTOANSWER		249
#define		HMI_LANG_CLARION_MIC			250
#define		HMI_LANG_CLARION_INTERNAL		251
#define		HMI_LANG_CLARION_EXTERNAL		252
#define		HMI_LANG_CLARION_MICGAIN		253
#define		HMI_LANG_CLARION_INQUIRING		254
#define		HMI_LANG_CLARION_DEVICEFOUNT	255
#define		HMI_LANG_CLARION_PAIR			256
#define		HMI_LANG_CLARION_DIALER			257
#define		HMI_LANG_CLARION_CALL			258
#define		HMI_LANG_CLARION_CONNECTED		259
#define		HMI_LANG_CLARION_END			260
#define		HMI_LANG_CLARION_KEYPAD			261
#define		HMI_LANG_CLARION_SPEAKER		262
#define		HMI_LANG_CLARION_HOLD			263
#define		HMI_LANG_CLARION_MUTE			264
#define		HMI_LANG_CLARION_ENTERPINCODE	265
#define		HMI_LANG_CLARION_PAIRING		266
#define		HMI_LANG_CLARION_CUT			267
#define		HMI_LANG_CLARION_DIALED			268
#define		HMI_LANG_CLARION_DIALEDNUMBERS	269
#define		HMI_LANG_CLARION_RECEIVED		270
#define		HMI_LANG_CLARION_RECEIVEDCALLS	271
#define		HMI_LANG_CLARION_MISSED			272
#define		HMI_LANG_CLARION_MISSEDCALLS	273
#define		HMI_LANG_CLARION_CONTACTS		274
#define		HMI_LANG_CLARION_FAILEDPAIR		275
#define		HMI_LANG_CLARION_INITIALIZING	276
#define		HMI_LANG_CLARION_PAIRSUCCESS	277
#define		HMI_LANG_CLARION_SELECTIMAGE	278
#define		HMI_LANG_CLARION_RECEIVECALL	279
#define		HMI_LANG_CLARION_HOLDCALL		280
#define		HMI_LANG_CLARION_ENDCALL		281
#define		HMI_LANG_CLARION_FORGETDEVICE	282
#define		HMI_LANG_CLARION_UNKNOWN		283
#define		HMI_LANG_CLARION_SIMPLE		    284
#define     HMI_LANG_CLARION_CONTROL		285
#define		HMI_LANG_CLARION_SIMPLEMODE		286
#define     HMI_LANG_CLARION_MENU			287
#define		HMI_LANG_CLARION_REPEAT			288
#define		HMI_LANG_CLARION_REARCONTROL	289
#define		HMI_LANG_CLARION_CAUTION		290
#define		HMI_LANG_CLARION_SAFETY			291
#define		HMI_LANG_CLARION_CAMERA			292
#define		HMI_LANG_CLARION_NOVIDEOSIGNAL	293
#define		HMI_LANG_CLARION_DVBT			294
#define		HMI_LANG_CLARION_MEDIADIRECT	295
#define		HMI_LANG_CLARION_ROTATION		296
#define		HMI_LANG_CLARION_EFFECT			297
#define		HMI_LANG_CLARION_TOPMENU		298
#define		HMI_LANG_CLARION_ROOT			299
#define		HMI_LANG_CLARION_AUDIO			300
#define		HMI_LANG_CLARION_LIST			301
#define		HMI_LANG_CLARION_INFO			302
#define		HMI_LANG_CLARION_SUBTITLE		303
#define		HMI_LANG_CLARION_DISCTITLE		304
#define		HMI_LANG_CLARION_CHAPTER		305
#define		HMI_LANG_CLARION_PARENTCONTROL	306
#define		HMI_LANG_CLARION_INPUTPASSWORD	307
#define		HMI_LANG_CLARION_MEDIA			308
#define		HMI_LANG_CLARION_TIME			309
#define		HMI_LANG_CLARION_BITRATE		310
#define		HMI_LANG_CLARION_ANGLE			311
#define		HMI_LANG_CLARION_DONE			312
#define		HMI_LANG_CLARION_MYUSB			313
#define		HMI_LANG_CLARION_FOLDERREPEAT	314
#define		HMI_LANG_CLARION_TRACKREPEAT	315
#define		HMI_LANG_CLARION_FOLDERRANDOM	316
#define		HMI_LANG_CLARION_RANDOMOFF      317
#define		HMI_LANG_CLARION_TRACKSCAN		318
#define		HMI_LANG_CLARION_FILENOTSUPPORT 319
#define		HMI_LANG_CLARION_VIDEOSCAN		320
#define		HMI_LANG_CLARION_AUDIOONLY		321
#define		HMI_LANG_CLARION_REARSOURCE		322
#define		HMI_LANG_CLARION_ENTERSYSTEM	323
#define		HMI_LANG_CLARION_ENTERCODE		324
#define		HMI_LANG_CLARION_CODEINCORRECT	325
#define		HMI_LANG_CLARION_ANTITHEFT		326
#define		HMI_LANG_CLARION_FRONT			327
#define		HMI_LANG_CLARION_REAR			328
#define		HMI_LANG_CLARION_SETTING		329
#define		HMI_LANG_CLARION_TUNER			330
#define		HMI_LANG_CLARION_BTAUDIO		331
#define		HMI_LANG_CLARION_BTTEL			332
#define		HMI_LANG_CLARION_IPODAUDIO		333
#define		HMI_LANG_CLARION_IPODVIDEO		334
#define		HMI_LANG_CLARION_DISCAUDIO		335
#define		HMI_LANG_CLARION_DISCVIDEO		336
#define		HMI_LANG_CLARION_USBAUDIO		337
#define		HMI_LANG_CLARION_USBVIDEO		338
#define		HMI_LANG_CLARION_NAVIGATION		339
#define		HMI_LANG_CLARION_2ZONEOFF		340
#define		HMI_LANG_CLARION_SETANTITHEFT   341
#define		HMI_LANG_CLARION_ERASEANTITHEFT	342
#define		HMI_LANG_CLARION_CONFIRMCODE    343
#define		HMI_LANG_CLARION_ERASECODE		344
#define		HMI_LANG_CLARION_SETCODE		345
#define		HMI_LANG_CLARION_IMAGE1			346
#define		HMI_LANG_CLARION_IMAGE2			347
#define		HMI_LANG_CLARION_IMAGE3			348
#define		HMI_LANG_CLARION_IMAGE4			349
#define		HMI_LANG_CLARION_IMAGE5			350
#define		HMI_LANG_CLARION_IMAGE6			351
#define		HMI_LANG_CLARION_IMAGE7			352
#define		HMI_LANG_CLARION_IMAGE8			353
#define		HMI_LANG_CLARION_IMAGE9			354
#define		HMI_LANG_CLARION_IMAGE10		355
#define		HMI_LANG_CLARION_IMPORTED		356
#define		HMI_LANG_CLARION_IMPORT			357
#define		HMI_LANG_CLARION_IMPORTUSB		358
#define		HMI_LANG_CLARION_LOADUSB		359
#define		HMI_LANG_CLARION_CODENOTMATCH	360
#define		HMI_LANG_CLARION_PERCODESET		361
#define		HMI_LANG_CLARION_ENTERNEWCODE	362
#define		HMI_LANG_CLARION_PASSSETSUCCESS 363
// #define		HMI_LANG_CLARION_PRESETSCANCH1  364
// #define		HMI_LANG_CLARION_PRESETSCANCH2  365
// #define		HMI_LANG_CLARION_PRESETSCANCH3  366
// #define		HMI_LANG_CLARION_PRESETSCANCH4  367
// #define		HMI_LANG_CLARION_PRESETSCANCH5  368
// #define		HMI_LANG_CLARION_PRESETSCANCH6  369
#define		HMI_LANG_CLARION_PRESETSCANCH	364
#define		HMI_LANG_CLARION_PRESETSCANCH1	365
#define		HMI_LANG_CLARION_AUTOSCANCH		366
#define		HMI_LANG_CLARION_DXSEEK			370
#define		HMI_LANG_CLARION_LOCALSEEK		371
#define		HMI_LANG_CLARION_REFRESH		372
#define		HMI_LANG_CLARION_KEYPADON		373
#define		HMI_LANG_CLARION_KEYPADOFF		374
#define		HMI_LANG_CLARION_PLAYLISTS		375
#define		HMI_LANG_CLARION_COMPOSERS		376
#define		HMI_LANG_CLARION_AUDIOBOOKS		377
#define		HMI_LANG_CLARION_PODCASTS		378
#define		HMI_LANG_CLARION_SONGS			379
#define		HMI_LANG_CLARION_MOVIES			380
#define		HMI_LANG_CLARION_MUSICVIDEOS	381
#define		HMI_LANG_CLARION_TVSHOWS		382
#define		HMI_LANG_CLARION_VIDEOPODCASTS	383
#define		HMI_LANG_CLARION_RENTALS		384
#define		HMI_LANG_CLARION_CHAPTERREPEAT	385
#define		HMI_LANG_CLARION_TITLEREPEAT	386
#define		HMI_LANG_CLARION_INVALIDDISC	387
#define		HMI_LANG_CLARION_SYSTEMRESTART	388
#define		HMI_LANG_CLARION_PLEASEWAIT		389
#define		HMI_LANG_CLARION_TRAFFICINFO	390
#define		HMI_LANG_CLARION_ARTISTS		391
#define		HMI_LANG_CLARION_GENRES			392
#define		HMI_LANG_CLARION_ALBUMS			393
#define		HMI_LANG_CLARION_RANDOMON		394
#define		HMI_LANG_CLARION_FRONTSOURCE	395
#define		HMI_LANG_CLARION_REAR1			396
#define		HMI_LANG_CLARION_REAR2			397
#define		HMI_LANG_CLARION_REAR3			398
#define		HMI_LANG_CLARION_REAR4			399
#define		HMI_LANG_CLARION_REAR5			400
#define		HMI_LANG_CLARION_REAR6			401
#define		HMI_LANG_CLARION_REAR7			402
#define		HMI_LANG_CLARION_REAR8			403
#define		HMI_LANG_CLARION_REAR9			404
#define		HMI_LANG_CLARION_SYSTEMLOCKED	405
#define		HMI_LANG_CLARION_DISCNOTSUPPORT	406
#define		HMI_LANG_CLARION_DISCNOTAVAIL	407
#define		HMI_LANG_CLARION_REGIONCODEERR	408
#define		HMI_LANG_CLARION_MONITOROFF		409
#define		HMI_LANG_CLARION_TOUCHSCREEN	410
#define		HMI_LANG_CLARION_RESOLUTIONNOT	411
#define		HMI_LANG_CLARION_VIDEOFRAMENOT	412
#define		HMI_LANG_CLARION_AUDIOFORMATNOT	413
#define		HMI_LANG_CLARION_PASSWORDTITLE	414
#define		HMI_LANG_CLARION_ANSWERTEL		415
#define		HMI_LANG_CLARION_ENDTEL			416
#define		HMI_LANG_CLARION_JAPANESE		415
#define		HMI_LANG_CLARION_JAPANESE2		416
#define		HMI_LANG_CLARION_ENGLISH2		417
#define		HMI_LANG_CLARION_CHINESE2		418
#define		HMI_LANG_CLARION_BTCALLANSWER	419
#define		HMI_LANG_CLARION_STOP_BTN		420