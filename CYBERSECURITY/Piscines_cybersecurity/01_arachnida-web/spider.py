import requests
import os
import argparse
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse


visited = set()

IMAGE_EXTENSIONS = (".jpg", ".jpeg", ".png", ".gif", ".bmp")


def download_image(url, folder):
    try:
        response = requests.get(url, timeout=10)
        if response.status_code != 200:
            print(f"[!] Failed ({response.status_code}): {url}")
            return
        filename = os.path.join(folder, url.split("/")[-1].split("?")[0])
        with open(filename, "wb") as f:
            f.write(response.content)
        print(f"[+] Downloaded: {filename}")
    except Exception as e:
        print(f"[!] Failed: {url} ({e})")


def collect_images(soup, base_url):
    images = set()
    for img in soup.find_all("img"):
        src = img.get("src")
        if src:
            images.add(urljoin(base_url, src))
    for link in soup.find_all("a"):
        href = link.get("href")
        if href and urljoin(base_url, href).lower().endswith(IMAGE_EXTENSIONS):
            images.add(urljoin(base_url, href))
    return images


def collect_links(soup, base_url):
    links = set()
    for link in soup.find_all("a"):
        href = link.get("href")
        if not href:
            continue
        next_url = urljoin(base_url, href)
        if urlparse(next_url).netloc == urlparse(base_url).netloc:
            links.add(next_url)
    return links


def spider(url, depth, max_depth, folder, recursive):
    if depth > max_depth or url in visited:
        return

    visited.add(url)

    try:
        response = requests.get(url, timeout=10)
        soup = BeautifulSoup(response.text, "html.parser")
    except Exception as e:
        print(f"[!] Error accessing {url} ({e})")
        return

    for img_url in collect_images(soup, url):
        if img_url.lower().endswith(IMAGE_EXTENSIONS):
            download_image(img_url, folder)

    if recursive:
        for next_url in collect_links(soup, url):
            spider(next_url, depth + 1, max_depth, folder, recursive)


def main():

    parser = argparse.ArgumentParser()

    parser.add_argument("url")
    parser.add_argument("-r", action="store_true")
    parser.add_argument("-l", type=int, default=5)
    parser.add_argument("-p", default="./data/")

    args = parser.parse_args()

    os.makedirs(args.p, exist_ok=True)

    spider(args.url, 0, args.l, args.p, args.r)


if __name__ == "__main__":
    main()