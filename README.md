## Thông tin sinh viên

**MÔN HỌC:** Cấu trúc dữ liệu và giải thuật  
**THỜI GIAN HỌC:** HK2(2025-2026),từ tháng 3 đến tháng 7

**HỌ VÀ TÊN SINH VIÊN:** Lê Trung Vinh  **MSSV:** 25120470  

**HỌ VÀ TÊN SINH VIÊN:** Huỳnh Trịnh Chí Tài
**MSSV:** 25120431

**HỌ VÀ TÊN SINH VIÊN:** Nguyễn Trương Đức Tiến
**MSSV:** 25120446

# BÁO CÁO: PHÂN TÍCH VÀ TỐI ƯU HÓA CÁC THUẬT TOÁN SẮP XẾP

---

# Bài A – Sắp xếp mảng số nguyên

## 1.1. Thuật toán lần 1 – Optimized Quick Sort

Sử dụng Quick Sort tối ưu với 4 kỹ thuật:

- **Median-of-Three Pivot:** Chọn trung vị của phần tử đầu, giữa, cuối làm pivot → giảm nguy cơ suy biến O(n²) trên mảng đã sắp xếp.
- **Hoare Partition:** Hai con trỏ từ hai đầu vào giữa → ít swap hơn Lomuto, xử lý phần tử trùng tốt hơn.
- **Insertion Sort khi n < 15:** Tránh overhead đệ quy trên đoạn nhỏ.
- **Tail Recursion Optimization:** Luôn đệ quy vào nửa nhỏ trước → chiều sâu stack O(log n) thay vì O(n).

**Độ phức tạp:** TB O(n log n), bộ nhớ phụ O(log n).

**So sánh lý do chọn:** Quick Sort tối ưu nhanh hơn Merge Sort (không cần O(n) bộ nhớ), ổn định hơn Quick Sort cơ bản, thực tế nhanh hơn Heap Sort nhờ hằng số nhỏ.

---

## 1.2. Bộ sinh test

| Test | Đặc điểm | Mục tiêu tấn công |
|---|---|---|
| 1 | 100.000 số ngẫu nhiên, XOR/dịch bit, xen kẽ âm/dương | Bubble/Selection/Insertion Sort (O(n²)); Quick Sort (phải xử lý toàn cây) |
| 2 | 100.000 số có quy luật (i×256, XOR bit cao), phân bố rộng | Radix Sort (miền giá trị lớn); Quick Sort (chất lượng pivot nhạy cảm) |
| 3 | 100.000 số ngẫu nhiên, XOR/dịch bit nhiều tầng, xen kẽ âm/dương | Tất cả thuật toán; Radix Sort khó xử lý âm+dương+miền rộng |
| 4 | 1 phần tử INT_MIN | Mọi thuật toán – kiểm tra biên; Radix/Counting Sort dễ overflow với abs(INT_MIN) |
| 5 | 100.000 số, seed cố định 123456789, có tính tái lập | Đánh giá khách quan hiệu năng trung bình của mọi thuật toán |

---

## 1.3. Thuật toán lần 2 – LSD Radix Sort Base 256

**So sánh lần 1 vs lần 2:**

| Tiêu chí | Lần 1 (Quick Sort) | Lần 2 (Radix Sort) |
|---|---|---|
| Độ phức tạp | O(n log n) | O(n) (4 pass × n) |
| Phép so sánh | Nhiều | Không có |
| Đệ quy | Có | Không |
| IO | cin/cout | fread/fwrite + buffer thủ công |

**Kỹ thuật tối ưu lần 2:** Không dùng phép so sánh; xử lý từng byte bằng `(v >> shift) & 0xFF`; thu thống kê 4 byte trong 1 lần duyệt; mảng tĩnh thay cấp phát động; truy cập tuần tự (cache-friendly); xử lý số âm bằng XOR `0x80000000`; Fast IO.

---

# Bài B – Sắp xếp chuỗi

## 2.1. Thuật toán lần 1 – 3-Way String Quicksort

Phân hoạch theo ký tự tại vị trí `d` thành 3 vùng: nhỏ hơn / bằng / lớn hơn pivot. Nhóm bằng tiếp tục xử lý ở `d+1`.

**Kỹ thuật tối ưu:**
- Chỉ đọc ký tự tại `d`, dừng ngay khi khác → không đọc lại tiền tố chung.
- `charAt()` trả về -1 khi hết chuỗi → xử lý độ dài khác nhau tự nhiên.
- `ios::sync_with_stdio(false)` giảm chi phí IO.

**So sánh:** Quick Sort chuỗi O(n·L·log n) vs Merge Sort O(n·L·log n) vs **3-Way String QS O(n·L) TB** – tiền tố chung chỉ xử lý một lần.

---

## 2.2. Bộ sinh test

Mỗi chuỗi dạng: `[tiền tố dài] + [mã nhóm] + [đuôi 4 ký tự]`. Các chuỗi cùng nhóm có tiền tố chung rất dài, nhắm vào MSD Radix Sort (phải khởi tạo bảng đếm nhiều mức, đệ quy sâu khi LCP dài).

| Test | Chiến lược | Tác động |
|---|---|---|
| 1 | 3125 nhóm × 32, tiền tố ~90 ký tự | Chiều rộng: 3125 bucket, mỗi bucket đệ quy ~90 mức |
| 2 | 6250 nhóm × 16, tiền tố ~90 ký tự | Kích thước 16 liên tục kích hoạt Insertion Sort |
| 3 | 2500 nhóm × 32, tiền tố ~95 ký tự | Chiều sâu: ~95 mức trước khi phân tách |
| 4 | 2000 nhóm × 50, tiền tố ~96, không xáo trộn | Chiều sâu + bucket lớn tiếp tục đệ quy rất sâu |
| 5 | Bucket 16/32 xen kẽ, tiền tố ~70 | Kết hợp cả chiều rộng lẫn chiều sâu |

---

## 2.3. Thuật toán lần 2 – MSD Radix Sort + Hybrid Insertion Sort

**Hạn chế lần 1:** Vẫn dựa trên so sánh; chưa tận dụng bảng chữ cái 26 ký tự; swap `std::string` tốn kém; cin/cout chậm.

**Kỹ thuật tối ưu lần 2:**
- **MSD Radix Sort:** Phân phối theo ký tự, không so sánh chuỗi.
- **Bảng đếm `cnt[27]`:** Nhỏ hơn 9,5 lần so với `cnt[256]`, dễ cache.
- **Sắp xếp trên mảng chỉ số:** Chỉ di chuyển số nguyên thay vì chuỗi thật.
- **Hybrid Insertion Sort (n ≤ 32):** Tránh overhead khởi tạo bảng đếm với bucket nhỏ.
- **`less_suffix(depth)`:** So sánh bắt đầu từ `depth`, không đọc lại tiền tố.
- **`fread` toàn bộ vào buffer:** Chuỗi chỉ là con trỏ vào buffer, không cấp phát động.
- **`fwrite` buffer xuất:** Giảm số lần syscall.
- **Lưu sẵn độ dài chuỗi:** Không gọi `strlen()` khi xuất.

---

# Bài C – Sắp xếp chuỗi theo độ dài và từ điển

## 3.1. Thuật toán lần 1 – Bucket Sort + MSD Radix Sort

**Bucket Sort theo độ dài:** `vector<string> a[101]` → chia bài toán lớn thành các nhóm cùng độ dài, loại bỏ phép so sánh chênh lệch độ dài, O(N).

**MSD Radix Sort:** Tại mỗi vị trí `pos`, dùng Counting Sort với `cnt[27]` để phân phối vào các bucket theo ký tự, rồi đệ quy. Độ phức tạp O(W) với W là tổng độ dài chuỗi.
---

## 3.2. Bộ sinh test

| Test | Cấu trúc | Mục tiêu tấn công |
|---|---|---|
| 1 | N=9999, tiền tố 2 ký tự giảm dần + 100 ký tự `a`, chu kỳ 676 | Quick Sort không tối ưu pivot → cây đệ quy lệch → O(N²) |
| 2 | N=9999, dài 100: 2 ký tự nghịch thế + 97 ký tự `b` + 1 ký tự phân định | Buộc đọc 97 ký tự giống nhau trước khi tìm điểm khác → O(N²×L) |
| 3 | N=9999, 25 chuỗi giống nhau/khối, tiền tố giảm dần + nhảy vọt | Quick Sort thiếu phân hoạch 3 chiều → hoán vị dư thừa → O(N²) |
| 4 | N=9999, LCP 97 ký tự, điểm phân định ở vị trí 98 | Chi phí so sánh O(L) → Quick Sort|
| 5 | N=9999, LCP 99 ký tự, khối tăng dần xen kẽ nội bộ giảm dần | Chi phí so sánh cực đại|

---

## 3.3. Thuật toán lần 2 – Multi-Key Quicksort + Memory Pool

**Vấn đề lần 1:** `std::string` + `std::vector` → cấp phát động liên tục, cache miss, bộ nhớ phụ lớn (mảng `temp` ở mỗi tầng đệ quy).

**Kỹ thuật tối ưu lần 2:**

- **Memory Pool (`char pool_buf[MAX_BUF]`):** Toàn bộ chuỗi liên tiếp trên RAM, `str_ptrs[i]` là con trỏ vào pool → cache-friendly, không cấp phát động.
- **Index Sorting:** Chỉ hoán vị số nguyên `A[i]`, `A[j]` thay vì di chuyển chuỗi thật → swap O(1).
- **Ad-hoc Linked List gom nhóm độ dài:** Mảng `head[len]` + `next_idx[i]` thay `vector<string> a[101]` → O(N), không cấp phát heap.
- **Multi-Key Quicksort (mkqsort):** Kết hợp Quick Sort và Radix Sort – phân 3 ngôi (< / = / >) theo 1 ký tự tại `depth`; phần `==` đệ quy với `depth+1` (như MSD Radix Sort), phần `<` và `>` đệ quy với `depth` giữ nguyên (như Quick Sort).

**So sánh lần 1 vs lần 2:**

| Tiêu chí | Lần 1 | Lần 2 |
|---|---|---|
| Bộ nhớ | Phân mảnh, cấp phát động | Memory Pool, liên mạch |
| Cache | Kém | Tốt |
| Bộ nhớ phụ | Cao (mảng `temp`) | Thấp (mảng chỉ số) |
| Hoán vị | O(L) | O(1) |
| Đoạn ngắn | Overhead khởi tạo `cnt` | Chia 3 ngôi trực tiếp |

---

*Hết báo cáo.*