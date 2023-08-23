# Canvas downloader for Linux!
This downloader is created for CS64-M23 in UCSB, if you want to use it for other canvas courses or other institutions, please edit the "downloader" file to put in the URL of your LMS.

# CS64 students please read:
## First time users:
### Installation:
To install this script on **CSIL**, please type in the following command:
```{bash}
cd ~
mkdir bin
cp /cs/student/tianleyu/bin/cs64 ~/bin
chmod 700 ~/bin/cs64
```

If the command above fails to work or you want to install it **outside of csil**, run following commands:
```{bash}
cd ~
mkdir bin
cd bin
wget https://cdn.jsdelivr.net/gh/yuxiaolejs/canvas-downloader/cs64
chmod 700 ~/bin/cs64
```
Please make sure ~/bin is in your PATH. You can check it by running
```
echo $PATH
```
### Configuration:
To make this script work for you, you need to tell it the API token for your canvas account. To do so, you just need to run the program, and copy paste your token:

First, you need to get an API token from canvas:
- Goto [https://ucsb.instructure.com/profile/settings](https://ucsb.instructure.com/profile/settings)
- Scroll down to **Approved Integrations**
- Click on **New Access Token**
- Name it
- Generate it
- Copy it

*Notice that this token will only be shown to you once, please complete all following steps before closing the prompt*

Then, you need to import it to the downloader:

Run the program by typing
```
cs64
```
Then you should see this prompt
```
Failed to load canvas token, please make sure the token is stored in ~/.canvas_token
To create that file, please enter your token: 
```
Paste the token you just copied from canvas and hit enter, you should see an interface like this:
```
====== Canvas File Downloader for Linux ======

Step 1/3: Select a module
----------------------------------------------
->Week 1
  Week 2
  Week 3
----------------------------------------------
Press W/S to select, and Enter to confirm

========== Version 0.0.1   @unicsyu ==========
```
Congratulations! It worked!

### Security concerns:
This program uses your canvas API token, which comes with full access to your canvas account. To prevent any possible security issue, this program stores your token locally in your home folder as a dot file (~/.canvas_token) in plain text. So, **do NOT use this program on untrusted devices** and please **NEVER share your .canvas_token file with anyone**. Login to canvas and delete the token **IMMEDIATELY** when you realized this token has been leaked out. Make sure other people have no permission to this file on the csil system!