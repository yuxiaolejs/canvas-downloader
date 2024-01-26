#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "multiLang.hpp"

using namespace std;

vector<map<string,string>> STR_CONST;
void multiLang::init()
{
    map<string,string> en_us;
    en_us.insert({"_dash", "----------------------------------------------"});
    en_us.insert({"_ddsh", "\n========== Version 0.0.3   @unicsyu =========="});
    en_us.insert({"_title", "====== Canvas File Downloader for Linux ======\n"});
    en_us.insert({"_cls", "\x1b[H\x1b[2J\x1b[H\x1b[f"});
    en_us.insert({"_subColor", "\x1b[3m"});
    en_us.insert({"_noStyle", "\x1b[0m"});
    en_us.insert({"_sel", "\x1b[2;30;47m"});
    en_us.insert({"_down", "\x1b[2;30;46m"});

    en_us.insert({"step0", "Step 0/4: Initialization"});
    en_us.insert({"step1", "Step 1/4: Select a course"});
    en_us.insert({"step2", "Step 2/4: Select a module"});
    en_us.insert({"step3", "Step 3/4: Select a file"});
    en_us.insert({"step4", "Step 4/4: Downloading"});
    en_us.insert({"tokenFail", "Failed to load canvas token, please make sure the token is stored in ~/.canvas_token\nMore details here: https://github.com/yuxiaolejs/canvas-downloader#configuration"});
    en_us.insert({"moduleUrlFail", "[fatal] failed to get url of module"});
    en_us.insert({"filesDownloaded", "Files downloaded:"});
    en_us.insert({"fileLocation", "Files can be found here:"});
    en_us.insert({"aborted", "Aborted"});
    en_us.insert({"moduleSel", "Press W/S to select, and Enter to confirm"});
    en_us.insert({"noFileInModule", "No file found in this module"});
    en_us.insert({"itemSel", "   W/S: Move  A: Add  D: Remove  ESC: Abort\n      Enter: Download files HIGHLIGHTED"});
    STR_CONST.push_back(en_us);

    map<string,string> zh_tw;
    zh_tw.insert({"_dash", "----------------------------------------------"});
    zh_tw.insert({"_ddsh", "\n========== 軟體版本 0.0.3   @unicsyu =========="});
    zh_tw.insert({"_title", "============  Canvas  文檔下載器  ============\n"});
    zh_tw.insert({"_cls", "\x1b[H\x1b[2J\x1b[H\x1b[f"});
    zh_tw.insert({"_subColor", "\x1b[3m"});
    zh_tw.insert({"_noStyle", "\x1b[0m"});
    zh_tw.insert({"_sel", "\x1b[2;30;47m"});
    zh_tw.insert({"_down", "\x1b[2;30;46m"});

    zh_tw.insert({"step0", "步驟 0/4: 初始化"});
    zh_tw.insert({"step1", "步驟 1/4: 選擇課程"});
    zh_tw.insert({"step2", "步驟 2/4: 選擇模塊"});
    zh_tw.insert({"step3", "步驟 3/4: 選擇文檔"});
    zh_tw.insert({"step4", "步驟 4/4: 正在下載"});
    zh_tw.insert({"tokenFail", "獲取Canvas密鑰失敗, 請確保密鑰文件存在 ~/.canvas_token\n更多詳情請訪問: https://github.com/yuxiaolejs/canvas-downloader#configuration"});
    zh_tw.insert({"moduleUrlFail", "[致命] 獲取文檔連結失敗"});
    zh_tw.insert({"filesDownloaded", "已下載:"});
    zh_tw.insert({"fileLocation", "文檔儲存位置:"});
    zh_tw.insert({"aborted", "已終止"});
    zh_tw.insert({"moduleSel", "按 W/S 選擇, 按 Enter 確認"});
    zh_tw.insert({"noFileInModule", "該模塊無文件"});
    zh_tw.insert({"itemSel", "   W/S: 選擇  A: 添加  D: 移除  ESC: 終止\n           Enter: 下載選擇的文檔"});
    STR_CONST.push_back(zh_tw);

    map<string,string> zh_cn;
    zh_cn.insert({"_dash", "----------------------------------------------"});
    zh_cn.insert({"_ddsh", "\n========== 软件版本 0.0.3   @unicsyu =========="});
    zh_cn.insert({"_title", "============  Canvas  文件下载器  ============\n"});
    zh_cn.insert({"_cls", "\x1b[H\x1b[2J\x1b[H\x1b[f"});
    zh_cn.insert({"_subColor", "\x1b[3m"});
    zh_cn.insert({"_noStyle", "\x1b[0m"});
    zh_cn.insert({"_sel", "\x1b[2;30;47m"});
    zh_cn.insert({"_down", "\x1b[2;30;46m"});

    zh_cn.insert({"step0", "步骤 0/4: 初始化"});
    zh_cn.insert({"step1", "步骤 1/4: 选择课程"});
    zh_cn.insert({"step2", "步骤 2/4: 选择模块"});
    zh_cn.insert({"step3", "步骤 3/4: 选择文件"});
    zh_cn.insert({"step4", "步骤 4/4: 正在下载"});
    zh_cn.insert({"tokenFail", "获取Canvas密钥失败, 请确保密钥保存在 ~/.canvas_token\n更多详情请访问: https://github.com/yuxiaolejs/canvas-downloader#configuration"});
    zh_cn.insert({"moduleUrlFail", "[致命] 获取文件链接失败"});
    zh_cn.insert({"filesDownloaded", "已下载:"});
    zh_cn.insert({"fileLocation", "文件保存位置:"});
    zh_cn.insert({"aborted", "已终止"});
    zh_cn.insert({"moduleSel", "按 W/S 选择, 按 Enter 确认"});
    zh_cn.insert({"noFileInModule", "该模块下无文件"});
    zh_cn.insert({"itemSel", "   W/S: 选择  A: 添加  D: 移除  ESC: 终止\n           Enter: 选择下载的文件"});
    STR_CONST.push_back(zh_cn);
}

string multiLang::get(int langIdx, string key)
{
    // cout << "Get "<< langIdx << ": " << key << endl;
    if(langIdx >= STR_CONST.size())
        return "UNDEFINED_STR_IDX";
    auto it = STR_CONST[langIdx].find(key);
    if(it==STR_CONST[langIdx].end())
        return "UNDEFINED_STR_KEY";
    else
        return it->second;
}