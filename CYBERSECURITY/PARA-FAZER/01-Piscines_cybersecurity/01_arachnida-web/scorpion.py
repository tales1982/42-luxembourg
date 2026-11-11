#!/usr/bin/env python3
import sys
import os
import datetime
from PIL import Image
from PIL.ExifTags import TAGS

IMAGE_EXTENSIONS = (".jpg", ".jpeg", ".png", ".gif", ".bmp")


def format_value(value):
    if isinstance(value, bytes):
        return value.decode("utf-8", errors="replace")
    return value


def display_metadata(filepath):
    print(f"\n{'='*55}")
    print(f"  File: {filepath}")
    print(f"{'='*55}")

    ext = os.path.splitext(filepath)[1].lower()
    if ext not in IMAGE_EXTENSIONS:
        print(f"  [!] Unsupported extension: {ext}")
        return

    if not os.path.isfile(filepath):
        print(f"  [!] File not found.")
        return

    stat = os.stat(filepath)
    mtime = datetime.datetime.fromtimestamp(stat.st_mtime)
    try:
        ctime = datetime.datetime.fromtimestamp(stat.st_birthtime)
    except AttributeError:
        ctime = datetime.datetime.fromtimestamp(stat.st_ctime)

    print(f"  {'File size':<28}: {stat.st_size} bytes")
    print(f"  {'Created':<28}: {ctime.strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"  {'Last modified':<28}: {mtime.strftime('%Y-%m-%d %H:%M:%S')}")

    try:
        img = Image.open(filepath)
        print(f"  {'Format':<28}: {img.format}")
        print(f"  {'Mode':<28}: {img.mode}")
        print(f"  {'Dimensions':<28}: {img.width} x {img.height} px")

        try:
            exif = img.getexif()
            if exif:
                print(f"\n  --- EXIF Data ---")
                for tag_id, value in exif.items():
                    tag_name = TAGS.get(tag_id, f"Tag_{tag_id}")
                    print(f"  {tag_name:<28}: {format_value(value)}")
            else:
                print(f"\n  No EXIF data.")
        except Exception:
            print(f"\n  No EXIF data.")

        if img.info:
            extra = {k: v for k, v in img.info.items() if k != "exif"}
            if extra:
                print(f"\n  --- {img.format} Metadata ---")
                for key, value in extra.items():
                    print(f"  {str(key):<28}: {format_value(value)}")

    except Exception as e:
        print(f"  [!] Error reading image: {e}")


def main():
    if len(sys.argv) < 2:
        print(f"Usage: ./scorpion FILE1 [FILE2 ...]")
        sys.exit(1)

    for filepath in sys.argv[1:]:
        display_metadata(filepath)


if __name__ == "__main__":
    main()
