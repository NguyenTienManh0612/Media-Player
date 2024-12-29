# Mediapp README

## Hướng dẫn sử dụng
Hãy làm theo những hướng dẫn dưới đây để có trải nghiệm tốt nhất:

### 1. **Khởi chạy ứng dụng**
- **Mở app Mediaplayer trước app Home** để app Home có thể set ngôn ngữ cho app Mediaplayer.

### 2. **Lần đầu build và chạy app**
Khi chạy lần đầu, bạn có thể gặp log sau:
```
Directory does not exist: "/home/manh/Code/Mock Project/Qt__MOCK/QtMock/Mediaplayer/data"
```
Hãy thực hiện các bước sau:
- **Bước 1:** Truy cập vào tệp `musiclistcontroller.h`.
- **Bước 2:** Nhấn `CTRL + Click` vào hàm `getMusicFilePaths()` và chỉnh sửa đường dẫn:
  ```cpp
  loadMusic("/home/manh/Code/Mock Project/Qt__MOCK/QtMock/Mediaplayer/data");
  ```
  thành thư mục `Mediaplayer/data` trên máy tính của bạn.

- **Bước 3:** Thực hiện tương tự với tệp `videolistcontroller.h` bằng cách chỉnh sửa hàm `getVideoFilePaths()`.

### 3. **Giải quyết vấn đề hỗ trợ decode**
Nếu WSL của bạn không hỗ trợ một số codec video hoặc nhạc, ứng dụng có thể gặp lỗi **crash**. Hãy cài đặt plugin Gstreamer bằng lệnh sau:
```bash
sudo apt install gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav
```

### 4. **Chạy nhạc và video**
- **Video:** Nhấn nút "Play" để phát video. Video đầu tiên sẽ được load tự động.
- **Nhạc:** Tương tự, nhấn nút "Play" để phát nhạc.

