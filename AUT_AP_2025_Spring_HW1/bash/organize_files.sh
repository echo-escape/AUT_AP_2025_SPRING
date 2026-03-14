#!/bin/bash

# 输入验证

TARGET_DIR="$1"
DRY_RUN_FLAG="$2"

# 检查文件夹
if [ -z "$TARGET_DIR" ]; then
    echo "Error! Miss the target directory parameter!"
    echo "Usage: ./organize_files.sh <target_dir> [--dry-run]"
    exit 1
fi

if [ ! -d "$TARGET_DIR" ]; then
    echo "Error! The directory does not exist!"
    echo "Please check again!"
    exit 1
fi

echo "Great! The target directory is: $TARGET_DIR"
echo "------------------------------------------"

LOG_FILE="$TARGET_DIR/organizer_log.txt"
echo "Start to log at $(date + "%Y-%m-%d %H:%M:%S")" >> "$LOG_FILE"

# 遍历文件

echo "Start to iterate directory..."

find "$TARGET_DIR" -type f | while read -r file; do
    # basename 是一个专门用来只保留文件名的命令
    filename=$(basename "$file")
    extension="${filename##*.}"
    if [ "$filename" != "$extension" ]; then

        DEST_DIR="$TARGET_DIR/$extension"
        # -p 若已有文件夹则静默，不报错
        mkdir -p "$DEST_DIR"

        if [ "$DRY_RUN_FLAG" = "--dry-run" ]; then
            echo "[DRY-RUN] Would move '$filename' to '$DEST_DIR/$filename'"
        else
            mv "$file" "$DEST_DIR"
            echo "Find file: $filename  --->  successfully put in [$extension]"
        fi

        CURRENT_TIME=$(date +"%Y-%m-%d %H:%M:%S")

        # 将详细信息按树状结构写入日志文件
        echo "[$CURRENT_TIME] 整理文件: $filename" >> "$LOG_FILE"
        echo "   ├── 原始位置: $file" >> "$LOG_FILE"
        echo "   └── 目标位置: $DEST_DIR" >> "$LOG_FILE"
        if [ "$DRY_RUN_FLAG" = "--dry-run" ]; then
            echo "   └── 状态: DRY-RUN (未实际移动)" >> "$LOG_FILE"
        fi
        echo "--------------------------------------------------" >> "$LOG_FILE"
    else
        echo "Skip file: $filename (without extension name)"
    fi
done

