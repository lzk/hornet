#include "error.h"
//#include "statusmonitor.h"
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif

enum{
    MSG_01001,
    MSG_01003,
    MSG_01030,
    MSG_01032,

    MSG_02008,
    MSG_02009,
    MSG_02011,
    MSG_02020,

    MSG_03009,
    MSG_03011,
    MSG_03013,
    MSG_03014,
    MSG_03015,
    MSG_03016,

    MSG_04003,
    MSG_04004,
    MSG_04010,
    MSG_04011,

    MSG_05021,
    MSG_05022,
    MSG_05020,
    MSG_05025,
    MSG_05002,
    MSG_05003,
    MSG_05004,
    MSG_05005,
    MSG_05006,
    MSG_05007,
    MSG_05008,
    MSG_05009,
    MSG_05010,
    MSG_05011,
    MSG_05012,
    MSG_05013,
    MSG_05014,
    MSG_05015,
    MSG_05016,
    MSG_05017,
    MSG_05018,
    MSG_05027,
    MSG_05032,
    MSG_05028,
    MSG_05029,
    MSG_05030,
    MSG_05031,
    MSG_05033,
    MSG_05034,
    MSG_05035,
    MSG_05036,
    MSG_05037,
    MSG_05043,
    MSG_05044,
    MSG_05045,
    MSG_05046,
    MSG_05072,
    MSG_05073,
};

static const Error_struct error_table[] =
{
	{
        .group = 1
		,.id = 1
    ,.code = "481-001"
    ,.string_index = MSG_01001
	}
	,{
        .group = 1
        ,.id = 3
    ,.code = "481-003"
    ,.string_index = MSG_01003
	}
	,{
        .group = 1
        ,.id = 30
    ,.code = "481-030"
    ,.string_index = MSG_01030
	}
	,{
        .group = 1
        ,.id = 32
    ,.code = "481-032"
    ,.string_index = MSG_01032
	}
	,{
		.group = 2
        ,.id = 8
    ,.code = "482-008"
    ,.string_index = MSG_02008
	}
    ,{
        .group = 2
        ,.id = 9
    ,.code = "482-009"
    ,.string_index = MSG_02009
    }
    ,{
        .group = 2
        ,.id = 11
    ,.code = "482-011"
    ,.string_index = MSG_02011
    }
    ,{
        .group = 2
        ,.id = 20
    ,.code = "482-020"
    ,.string_index = MSG_02020
    }
    ,{
        .group = 3
        ,.id = 9
    ,.code = "483-009"
    ,.string_index = MSG_03009
    }
    ,{
        .group = 3
        ,.id = 11
    ,.code = "483-011"
    ,.string_index = MSG_03011
    }
    ,{
        .group = 3
        ,.id = 13
    ,.code = "483-013"
    ,.string_index = MSG_03013
    }
    ,{
        .group = 3
        ,.id = 14
    ,.code = "483-014"
    ,.string_index = MSG_03014
    }
    ,{
        .group = 3
        ,.id = 15
    ,.code = "483-015"
    ,.string_index = MSG_03015
    }
    ,{
        .group = 3
        ,.id = 16
    ,.code = "483-016"
    ,.string_index = MSG_03016
    }
    ,{
        .group = 4
        ,.id = 3
    ,.code = "485-072"
    ,.string_index = MSG_04003
    }
    ,{
        .group = 4
        ,.id = 4
    ,.code = "484-004"
    ,.string_index = MSG_04004
    }
    ,{
        .group = 4
        ,.id = 10
    ,.code = "484-010"
    ,.string_index = MSG_04010
    }
    ,{
        .group = 4
        ,.id = 11
    ,.code = "484-011"
    ,.string_index = MSG_04011
    }
    ,{
        .group = 5
        ,.id = 21
    ,.code = "485-021"
    ,.string_index = MSG_05021
    }
    ,{
        .group = 5
        ,.id = 22
    ,.code = "485-022"
    ,.string_index = MSG_05022
    }
    ,{
        .group = 5
        ,.id = 20
    ,.code = "485-020"
    ,.string_index = MSG_05020
    }
    ,{
        .group = 5
        ,.id = 25
    ,.code = "485-025"
    ,.string_index = MSG_05025
    }
    ,{
        .group = 5
        ,.id = 2
    ,.code = "485-002"
    ,.string_index = MSG_05002
    }
    ,{
        .group = 5
        ,.id = 3
    ,.code = "485-003"
    ,.string_index = MSG_05003
    }
    ,{
        .group = 5
        ,.id = 4
    ,.code = "485-004"
    ,.string_index = MSG_05004
    }
    ,{
        .group = 5
        ,.id = 5
    ,.code = "485-005"
    ,.string_index = MSG_05005
    }
    ,{
        .group = 5
        ,.id = 6
    ,.code = "485-006"
    ,.string_index = MSG_05006
    }
    ,{
        .group = 5
        ,.id = 7
    ,.code = "485-007"
    ,.string_index = MSG_05007
    }
    ,{
        .group = 5
        ,.id = 8
    ,.code = "485-008"
    ,.string_index = MSG_05008
    }
    ,{
        .group = 5
        ,.id = 9
    ,.code = "485-009"
    ,.string_index = MSG_05009
    }
    ,{
        .group = 5
        ,.id = 10
    ,.code = "485-010"
    ,.string_index = MSG_05010
    }
    ,{
        .group = 5
        ,.id = 11
    ,.code = "485-011"
    ,.string_index = MSG_05011
    }
    ,{
        .group = 5
        ,.id = 12
    ,.code = "485-012"
    ,.string_index = MSG_05012
    }
    ,{
        .group = 5
        ,.id = 13
    ,.code = "485-013"
    ,.string_index = MSG_05013
    }
    ,{
        .group = 5
        ,.id = 14
    ,.code = "485-014"
    ,.string_index = MSG_05014
    }
    ,{
        .group = 5
        ,.id = 15
    ,.code = "485-015"
    ,.string_index = MSG_05015
    }
    ,{
        .group = 5
        ,.id = 16
    ,.code = "485-016"
    ,.string_index = MSG_05016
    }
    ,{
        .group = 5
        ,.id = 17
    ,.code = "485-017"
    ,.string_index = MSG_05017
    }
    ,{
        .group = 5
        ,.id = 18
    ,.code = "485-018"
    ,.string_index = MSG_05018
    }
    ,{
        .group = 5
        ,.id = 27
    ,.code = "485-027"
    ,.string_index = MSG_05027
    }
    ,{
        .group = 5
        ,.id = 32
    ,.code = "485-032"
    ,.string_index = MSG_05032
    }
    ,{
        .group = 5
        ,.id = 28
    ,.code = "485-028"
    ,.string_index = MSG_05028
    }
    ,{
        .group = 5
        ,.id = 29
    ,.code = "485-029"
    ,.string_index = MSG_05029
    }
    ,{
        .group = 5
        ,.id = 30
    ,.code = "485-030"
    ,.string_index = MSG_05030
    }
    ,{
        .group = 5
        ,.id = 31
    ,.code = "485-031"
    ,.string_index = MSG_05031
    }
    ,{
        .group = 5
        ,.id = 33
    ,.code = "485-033"
    ,.string_index = MSG_05033
    }
    ,{
        .group = 5
        ,.id = 34
    ,.code = "485-034"
    ,.string_index = MSG_05034
    }
    ,{
        .group = 5
        ,.id = 35
    ,.code = "485-035"
    ,.string_index = MSG_05035
    }
    ,{
        .group = 5
        ,.id = 36
    ,.code = "485-036"
    ,.string_index = MSG_05036
    }
    ,{
        .group = 5
        ,.id = 37
    ,.code = "485-037"
    ,.string_index = MSG_05037
    }
    ,{
        .group = 5
        ,.id = 43
    ,.code = "485-043"
    ,.string_index = MSG_05043
    }
    ,{
        .group = 5
        ,.id = 44
    ,.code = "485-044"
    ,.string_index = MSG_05044
    }
    ,{
        .group = 5
        ,.id = 45
    ,.code = "485-045"
    ,.string_index = MSG_05045
    }
    ,{
        .group = 5
        ,.id = 46
    ,.code = "485-046"
    ,.string_index = MSG_05046
    }
    ,{
        .group = 5
        ,.id = 72
    ,.code = "485-072"
    ,.string_index = MSG_05072
    }
    ,{
        .group = 5
        ,.id = 73
    ,.code = "484-004"
    ,.string_index = MSG_05073
    }
};

static const int error_table_size = sizeof(error_table) / sizeof(error_table[0]);

static const Error_String_struct error_string_table[] =
{
    {.string_index = MSG_01001
    ,.title = "打印机错误。"
    ,.mediaInfo = 0
    ,.lines = 2
    ,.line0 = "关闭打印机，然后再次打开它。"
    ,.line1 = "如果重复此故障，请与客户支持联系。"
    },{.string_index = MSG_01003
    ,.title = "打印机错误。"
    ,.mediaInfo = 0
    ,.lines = 2
       ,.line0 = "关闭打印机，然后再次打开它。"
       ,.line1 = "如果重复此故障，请与客户支持联系。"
    },{.string_index = MSG_01030
    ,.title = "打印机错误。"
    ,.mediaInfo = 0
    ,.lines = 2
       ,.line0 = "关闭打印机，然后再次打开它。"
       ,.line1 = "如果重复此故障，请与客户支持联系。"
    },{.string_index = MSG_01032
    ,.title = "出现固件下载格式错误。"
    ,.mediaInfo = 0
    ,.lines = 2
    ,.line0 = "请按[确定]按钮。"
       ,.line1 = "如果重复此故障，请与客户支持联系。"
      },{.string_index = MSG_02008
      ,.title = "打印机错误。"
      ,.mediaInfo = 0
      ,.lines = 2
      ,.line0 = "关闭打印机，然后再次打开它。"
      ,.line1 = "如果重复此故障，请与客户支持联系。"
      },{.string_index = MSG_02009
      ,.title = "打印机错误。"
      ,.mediaInfo = 0
      ,.lines = 2
         ,.line0 = "关闭打印机，然后再次打开它。"
         ,.line1 = "如果重复此故障，请与客户支持联系。"
      },{.string_index = MSG_02011
      ,.title = "打印机错误。"
      ,.mediaInfo = 0
      ,.lines = 2
         ,.line0 = "关闭打印机，然后再次打开它。"
         ,.line1 = "如果重复此故障，请与客户支持联系。"
      },{.string_index = MSG_03009
      ,.title = "发生PDL仿真错误。"
      ,.mediaInfo = 0
      ,.lines = 1
      ,.line0 = "按[确定]按钮清除错误并取消当前打印作业。"
      },{.string_index = MSG_03016
      ,.title = "发生PDL仿真错误。"
      ,.mediaInfo = 0
      ,.lines = 1
         ,.line0 = "按[确定]按钮清除错误并取消当前打印作业。"
    },{.string_index = MSG_04003
    ,.title = "打印机错误。"
    ,.mediaInfo = 0 + 2
    ,.lines = 1
    ,.line0 = "请插入"
    },{.string_index = MSG_04004
    ,.title = "未检测到纸张。"
    ,.mediaInfo = 1 + 2
    ,.lines = 4
    ,.line0 = "拉出"
    ,.line1 = "设置纸张和加载纸盒。"
    ,.line2 = "纸张大小： "
    ,.line3 = "纸张类型： "
    },{.string_index = MSG_04010
    ,.title = "指定的纸张不可用。"
    ,.mediaInfo = 1 + 2
    ,.lines = 3
    ,.line0 = "将指定的纸张装入"
    ,.line1 = "纸张大小： "
    ,.line2 = "纸张类型： "
    },{.string_index = MSG_04011
    ,.title = "指定的纸张不可用。"
       ,.mediaInfo = 1 + 2
       ,.lines = 3
       ,.line0 = "将指定的纸张装入"
       ,.line1 = "纸张大小： "
       ,.line2 = "纸张类型： "
    },{.string_index = MSG_05021
    ,.title = "定影器寿命尽。"
    ,.mediaInfo = 0
    ,.lines = 1
    ,.line0 = "请与客户支持联系。"
    },{.string_index = MSG_05022
    ,.title = "ITU寿命尽。"
    ,.mediaInfo = 0
    ,.lines = 1
    ,.line0 = "请与客户支持联系。"
    },{.string_index = MSG_05020
    ,.title = "四色硒鼓套件丢失或未完全插入打印机。"
    ,.mediaInfo = 0
    ,.lines = 1
    ,.line0 = "请插入四色硒鼓套件。"
    },{.string_index = MSG_05025
    ,.title = "废粉仓丢失或未完全插入打印机。"
    ,.mediaInfo = 0
    ,.lines = 1
    ,.line0 = "请插入废粉仓。"
      },{.string_index = MSG_05002
      ,.title = "黑色粉仓丢失或未完全插入打印机。"
      ,.mediaInfo = 0
      ,.lines = 1
      ,.line0 = "打开碳粉盒访问盖并确保已完全安装黑色粉仓。"
//      ,.line1 = "有关详细信息，请单击[显示操作方式]按钮。"
      },{.string_index = MSG_05003
      ,.title = "青色粉仓丢失或未完全插入打印机。"
      ,.mediaInfo = 0
      ,.lines = 1
      ,.line0 = "打开碳粉盒访问盖并确保已完全安装青色粉仓。"
//      ,.line1 = "有关详细信息，请单击[显示操作方式]按钮。"
      },{.string_index = MSG_05004
      ,.title = "品红色粉仓丢失或未完全插入打印机。"
      ,.mediaInfo = 0
      ,.lines = 1
      ,.line0 = "打开碳粉盒访问盖并确保已完全安装品红色粉仓。"
//      ,.line1 = "有关详细信息，请单击[显示操作方式]按钮。"
      },{.string_index = MSG_05005
      ,.title = "黄色粉仓丢失或未完全插入打印机。"
      ,.mediaInfo = 0
      ,.lines = 1
      ,.line0 = "打开碳粉盒访问盖并确保已完全安装黄色粉仓。"
//      ,.line1 = "有关详细信息，请单击[显示操作方式]按钮。"
      },{.string_index = MSG_05006
      ,.title = "出现卡纸。"
      ,.mediaInfo = 0
      ,.lines = 1
      ,.line0 = "拉出进纸盒1，取出卡纸。"
      },{.string_index = MSG_05007
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "拉出进纸盒2，取出卡纸。"
      },{.string_index = MSG_05008
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "拉出进纸盒3，取出卡纸。"
      },{.string_index = MSG_05009
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "拉出进纸盒1，取出卡纸。"
      },{.string_index = MSG_05010
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "拉出进纸盒2，取出卡纸。"
      },{.string_index = MSG_05011
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "拉出进纸盒3，取出卡纸。"
      },{.string_index = MSG_05012
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "拉出多功能进纸器，取出卡纸。"
      },{.string_index = MSG_05013
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "拉出进纸盒1，取出卡纸。"
      },{.string_index = MSG_05014
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "拉出多功能进纸器，取出卡纸。"
      },{.string_index = MSG_05015
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 2
         ,.line0 = "拉出纸盒，取出卡纸。"
      ,.line1 = "打开盖门，提起熔断单元松开拉杆，取出卡纸，关闭盖门。"
      },{.string_index = MSG_05016
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "打开盖门，提起熔断单元松开拉杆，取出卡纸，关闭盖门。"
      },{.string_index = MSG_05017
         ,.title = "出现卡纸。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "打开盖门，提起熔断单元松开拉杆，取出卡纸，关闭盖门。"
      },{.string_index = MSG_05018
      ,.title = "打印机错误。"
      ,.mediaInfo = 0
      ,.lines = 2
      ,.line0 = "关闭打印机，然后再次打开它。"
      ,.line1 = "如果重复此故障，请与客户支持联系。"
      },{.string_index = MSG_05027
         ,.title = "四色硒鼓套件寿命尽。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "请更换四色硒鼓套件。"
      },{.string_index = MSG_05032
         ,.title = "废粉仓满。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "请更换废粉仓。"
      },{.string_index = MSG_05028
      ,.title = "更换不支持的黑色粉仓。"
      ,.mediaInfo = 0
      ,.lines = 1
      ,.line0 = "打开碳粉盒入口盖，然后卸下所用的黑色粉仓并安装一个支持的黑色粉仓。"
      },{.string_index = MSG_05029
         ,.title = "更换不支持的青色粉仓。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "打开碳粉盒入口盖，然后卸下所用的青色粉仓并安装一个支持的青色粉仓。"
      },{.string_index = MSG_05030
         ,.title = "更换不支持的品红色粉仓。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "打开碳粉盒入口盖，然后卸下所用的品红色粉仓并安装一个支持的品红色粉仓。"
      },{.string_index = MSG_05031
         ,.title = "更换不支持的黄色粉仓。"
         ,.mediaInfo = 0
         ,.lines = 1
         ,.line0 = "打开碳粉盒入口盖，然后卸下所用的黄色粉仓并安装一个支持的黄色粉仓。"
      },{.string_index = MSG_05033
      ,.title = "更换黑色粉仓。"
      ,.mediaInfo = 0
      ,.lines = 1
         ,.line0 = "打开碳粉盒入口盖，然后卸下所用的黑色粉仓并安装一个新的黑色粉仓。"
      },{.string_index = MSG_05034
         ,.title = "更换青色粉仓。"
         ,.mediaInfo = 0
         ,.lines = 1
            ,.line0 = "打开碳粉盒入口盖，然后卸下所用的青色粉仓并安装一个新的青色粉仓。"
      },{.string_index = MSG_05035
         ,.title = "更换品红色粉仓。"
         ,.mediaInfo = 0
         ,.lines = 1
            ,.line0 = "打开碳粉盒入口盖，然后卸下所用的品红色粉仓并安装一个新的品红色粉仓。"
      },{.string_index = MSG_05036
         ,.title = "更换黄色粉仓。"
         ,.mediaInfo = 0
         ,.lines = 1
            ,.line0 = "打开碳粉盒入口盖，然后卸下所用的黄色粉仓并安装一个新的黄色粉仓。"
      },{.string_index = MSG_05037
      ,.title = "机盖被打开。"
      ,.mediaInfo = 0
      ,.lines = 1
      ,.line0 = "请关闭所有盖门。"
      },{.string_index = MSG_05043
      ,.title = "需要立即更换黑色粉仓。"
      ,.mediaInfo = 0
      ,.lines = 1
         ,.line0 = "打开碳粉盒入口盖，然后卸下所用的黑色粉仓并安装一个新的黑色粉仓。"
      },{.string_index = MSG_05044
         ,.title = "需要立即更换青色粉仓。"
         ,.mediaInfo = 0
         ,.lines = 1
            ,.line0 = "打开碳粉盒入口盖，然后卸下所用的青色粉仓并安装一个新的青色粉仓。"
      },{.string_index = MSG_05045
         ,.title = "需要立即更换品红色粉仓。"
         ,.mediaInfo = 0
         ,.lines = 1
            ,.line0 = "打开碳粉盒入口盖，然后卸下所用的品红色粉仓并安装一个新的品红色粉仓。"
      },{.string_index = MSG_05046
         ,.title = "需要立即更换黄色粉仓。"
         ,.mediaInfo = 0
         ,.lines = 1
            ,.line0 = "打开碳粉盒入口盖，然后卸下所用的黄色粉仓并安装一个新的黄色粉仓。"
      },{.string_index = MSG_05072
      ,.title = "未插入进纸盒"
      ,.mediaInfo = 2
      ,.lines = 1
      ,.line0 = "请插入"
      },{.string_index = MSG_05073
         ,.title = "未检测到纸张。"
         ,.mediaInfo = 1
         ,.lines = 4
         ,.line0 = "拉出进纸盒1。"
         ,.line1 = "设置纸张和加载纸盒。"
         ,.line2 = "纸张大小： "
         ,.line3 = "纸张类型： "
      }
};

static const int error_string_table_size = sizeof(error_string_table) / sizeof(error_string_table[0]);

void PaperSize2Str(int bPaperSize, char* szPaperSize);
void PaperType2Str(int bPaperType, char* szPaperType);
ErrorInfo_struct getErrorInfo(int group ,int id ,int paperType ,int paperSize ,int paperTray)
{
    ErrorInfo_struct errorInfo;
    memset((void*)&errorInfo ,0 ,sizeof(errorInfo));
    const Error_struct* p_error;
    const Error_String_struct* p_errorString;
    int i ,j;
    for(i = 0 ;i < error_table_size ;i++){
        p_error = &error_table[i];
        if(p_error->group == group && p_error->id == id){
            errorInfo.error = p_error;
            for(j = 0 ;j < error_string_table_size ;j++){
                p_errorString = &error_string_table[j];
                if(p_errorString->string_index == p_error->string_index){
                    errorInfo.errorString = p_errorString;
                    if(!paperType)
                        break;
                    if((p_errorString->mediaInfo & 2) == 2){
                        switch (paperTray&7) {
                        case 2:
                            strcpy(errorInfo.paperTrayString, "进纸盒2。");
                            break;
                        case 3:
                            strcpy(errorInfo.paperTrayString, "进纸盒3。");
                            break;
                        case 4:
                            strcpy(errorInfo.paperTrayString, "多功能进纸器。");
                            break;
                        case 5:
                            strcpy(errorInfo.paperTrayString, "手动进纸器。");
                            break;
                        case 1:
                        default:
                            strcpy(errorInfo.paperTrayString, "进纸盒1。");
                            break;
                        }
                    }

                    if(p_errorString->lines < 3)
                        break;
                    if((p_errorString->mediaInfo & 1) == 1){
                        PaperSize2Str(paperSize ,errorInfo.paperSizeString);
                        PaperType2Str(paperType ,errorInfo.paperTypeString);
                    }
                    break;
                }
            }
            break;
        }
    }
    return errorInfo;
}
#ifdef __cplusplus
}
#endif
