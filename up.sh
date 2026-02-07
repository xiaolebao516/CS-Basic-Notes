#!/bin/bash

# 1. 暂存所有更改
git add .

# 2. 提交，备注信息包含当前时间，这样你就不用每次想备注了
git commit -m "Update notes: $(date +'%Y-%m-%d %H:%M:%S')"

# 3. 推送到远程仓库
git push origin main

echo "✅ 笔记同步成功！"
read -p "按回车键退出..."