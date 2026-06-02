# BÁO CÁO: PHÂN TÍCH VÀ TỐI ƯU HÓA CÁC THUẬT TOÁN SẮP XẾP

---

# Bài A – Sắp xếp mảng số nguyên

## 1.1. Thuật toán lần 1 – Optimized Quick Sort

Quick Sort hoạt động theo nguyên tắc chọn pivot, phân hoạch mảng, đệ quy hai nửa. Độ phức tạp trung bình O(n log n).

**Các kỹ thuật tối ưu:**

- **Median-of-Three Pivot:** Chọn trung vị của ba phần tử (đầu, giữa, cuối) làm pivot, giảm nguy cơ suy biến O(n²) trên mảng đã sắp xếp.
- **Hoare Partition:** Hai con trỏ từ hai đầu chạy vào giữa, thực hiện ít swap hơn Lomuto, xử lý tốt dữ liệu trùng nhau.
- **Insertion Sort cho đoạn nhỏ (<15 phần tử):** Tránh overhead đệ quy, nhanh hơn Quick Sort khi n rất nhỏ.
- **Tail Recursion Optimization:** Luôn đệ quy vào nửa nhỏ trước, đảm bảo chiều sâu stack O(log n), giảm nguy cơ Stack Overflow.

**So sánh thuật toán:**

| Thuật toán | Thời gian TB | Bộ nhớ phụ |
|---|---|---|
| Bubble/Selection/Insertion Sort | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n) |
| Heap Sort | O(n log n) | O(1) |
| **Quick Sort tối ưu** | **O(n log n)** | **O(log n)** |

Lựa chọn Quick Sort tối ưu vì nhanh nhất trong thực tế, không tốn bộ nhớ phụ lớn, và bốn kỹ thuật trên loại bỏ hầu hết điểm yếu của Quick Sort cơ bản.

---

## 1.2. Bộ sinh test

| Test | Đặc điểm | Mục tiêu |
|---|---|---|
| 1 | 100.000 số ngẫu nhiên (mt19937, XOR, xen kẽ âm/dương) | Đánh giá hiệu năng thực tế tổng quát |
| 2 | 100.000 số có quy luật, phạm vi giá trị rất rộng | Kiểm tra Radix/Counting Sort trên miền rộng |
| 3 | 100.000 số ngẫu nhiên, XOR nhiều tầng | Đánh giá tổng quát, số âm+dương lẫn lộn |
| 4 | 1 phần tử: INT_MIN (-2147483648) | Kiểm tra biên, phát hiện overflow với abs(INT_MIN) |
| 5 | 100.000 số, seed cố định 123456789 | Đo hiệu năng tái lập, so sánh khách quan |

---

## 1.3. Thuật toán lần 2 – LSD Radix Sort Base 256

Chuyển từ Comparison Sort sang Non-Comparison Sort, giảm độ phức tạp từ O(n log n) xuống **O(n)** (4 pass × n).

**Các tối ưu so với lần 1:**

- **LSD Radix Sort:** Sắp xếp theo từng byte (4 byte/32-bit int), không dùng phép so sánh.
- **Fast IO (fread/fwrite + buffer thủ công):** Giảm đáng kể thời gian đọc/ghi.
- **Parse số thủ công:** Tránh overhead của iostream.
- **Xử lý bit trực tiếp:** `(v >> shift) & 0xFF` nhanh nhờ phép dịch bit.
- **Thống kê 4 pass trong 1 lần duyệt:** Giảm số lần quét mảng.
- **Mảng tĩnh thay cấp phát động:** Tăng cache locality.
- **Xử lý số âm bằng XOR 0x80000000:** Không cần tách riêng số âm/dương.
- **Loại bỏ hoàn toàn đệ quy:** Vòng lặp thuần túy, không overhead stack.

**Kết luận:** Lần 2 nhanh hơn đáng kể trên các bộ test lớn nhờ giảm độ phức tạp và tối ưu toàn diện từ IO đến xử lý bộ nhớ.

---

# Bài B – Sắp xếp chuỗi

## 2.1. Thuật toán lần 1 – 3-Way String Quicksort

Phân hoạch theo ký tự tại vị trí `d` thành 3 vùng: nhỏ hơn / bằng / lớn hơn pivot. Phần bằng đệ quy tiếp ở `d+1`.

**Tối ưu:**

- **So sánh từng ký tự:** Dừng ngay khi phát hiện khác biệt, không đọc lại tiền tố chung.
- **Phân hoạch 3 chiều:** Giảm số phép so sánh và đệ quy so với Quick Sort 2 chiều.
- **charAt() trả -1 khi hết chuỗi:** Xử lý chuỗi độ dài khác nhau tự nhiên theo thứ tự từ điển.
- **Fast IO:** `ios::sync_with_stdio(false); cin.tie(nullptr)`.

Độ phức tạp trung bình O(n·L). Tiền tố chung chỉ xử lý đúng một lần.

---

## 2.2. Bộ sinh test – Tấn công MSD Radix Sort

Chuỗi có dạng: `[tiền tố A] + [mã nhóm] + [tiền tố B] + [đuôi 4 ký tự]`. Chuỗi cùng nhóm có tiền tố chung rất dài, chỉ khác ở đuôi.

| Test | Chiến lược | Tác động lên MSD Radix Sort |
|---|---|---|
| 1 | 3125 bucket × 32, prefix ≈ 90 | Chiều rộng: nhiều bucket, mỗi bucket đệ quy ~90 mức |
| 2 | 6250 bucket × 16, prefix ≈ 90 | Liên tục kích hoạt Insertion Sort trong bucket nhỏ |
| 3 | 2500 bucket × 32, prefix ≈ 95 | Chiều sâu: đệ quy ~95 mức trước khi phân tách |
| 4 | 2000 bucket × 50, prefix ≈ 96, không xáo trộn | Bucket lớn + chiều sâu cực cao |
| 5 | Bucket 16/32 xen kẽ, prefix ≈ 70 | Kết hợp cả chiều rộng lẫn chiều sâu |

3-Way String Quicksort ít bị ảnh hưởng hơn vì không cần khởi tạo bảng đếm và xử lý tốt tiền tố chung qua phân hoạch 3 chiều.

---

## 2.3. Thuật toán lần 2 – MSD Radix Sort + Hybrid Insertion Sort

**Hạn chế lần 1:** Vẫn dùng phép so sánh, chưa tận dụng bảng chữ cái 26 ký tự, swap `std::string` tốn kém, chưa xử lý riêng bucket nhỏ.

**Các tối ưu lần 2:**

- **MSD Radix Sort:** Phân phối trực tiếp vào bucket theo ký tự, mỗi mức chỉ duyệt O(n), không so sánh chuỗi.
- **Bảng đếm `count[27]`:** Nhỏ hơn `count[256]` ~9.5 lần, dễ nằm trong cache CPU.
- **Sắp xếp trên mảng chỉ số:** Chỉ di chuyển số nguyên, không di chuyển chuỗi.
- **Hybrid Insertion Sort (n ≤ 32):** Tránh overhead khởi tạo bảng đếm và đệ quy cho bucket nhỏ.
- **`less_suffix(depth)`:** So sánh bắt đầu từ độ sâu hiện tại, bỏ qua phần tiền tố đã biết giống nhau — tiết kiệm ~90 lần đọc ký tự mỗi phép so sánh khi tiền tố dài 90 ký tự.
- **`fread` vào buffer duy nhất:** Chuỗi lưu dưới dạng con trỏ vào buffer, không cấp phát động.
- **`fwrite` qua buffer xuất:** Giảm số lần gọi hàm xuất OS.
- **Lưu trước độ dài chuỗi:** Không cần gọi lại `strlen()` khi xuất.

---

# Bài C – Sắp xếp chuỗi theo độ dài và từ điển

## 3.1. Thuật toán lần 1 – Bucket Sort + MSD Radix Sort

**Bucket Sort theo độ dài:** `vector<string> a[101]`, đẩy chuỗi vào bucket theo `s.size()`. Chia bài toán lớn thành các bài toán sắp xếp cùng độ dài, O(N).

**MSD Radix Sort:** Dùng `cnt[27]` + prefix sum để phân phối chuỗi vào bucket theo từng ký tự, đệ quy tiếp các bucket con. Độ phức tạp O(W) với W là tổng độ dài.

**Hướng tối ưu:** Dùng ngưỡng cắt `r-l < 15` chuyển sang `std::sort`; dùng `std::copy/move` thay loop khi sao chép mảng trung gian; chỉ duyệt đến độ dài tối đa thực tế thay vì cố định 101.

---

## 3.2. Bộ sinh test – Tấn công Quick Sort và MSD Radix Sort

| Test | Cấu trúc dữ liệu | Cơ chế tấn công | Mục tiêu |
|---|---|---|---|
| 1 | N=9999, tiền tố 2 ký tự giảm dần, thân 100×'a' | Mảng nghịch thế chu kỳ | Quick Sort cơ bản → O(N²) |
| 2 | N=9999, tiền tố 2 ký tự, thân 97×'b', hậu tố biến | Điểm phân định ở cuối, 97 ký tự tĩnh trước | Các thuật toán so sánh tuyến tính |
| 3 | N=9999, khối 25 chuỗi giống nhau, tiền tố 3 ký tự giảm dần | Trùng lặp gom nhóm + nghịch thế ngắt nhịp | Quick Sort không 3 chiều → O(N²) |
| 4 | N=9999, LCP 97 ký tự, ký tự phân định ở vị trí 98 | Chi phí mỗi phép so sánh đẩy lên O(L) | Quick Sort, TimSort |
| 5 | N=9999, LCP 99 ký tự, xen kẽ khối tăng–giảm | Tối đa hóa chi phí so sánh + phá vỡ logic gộp | Quick Sort, TimSort/Natural Merge Sort |

---

## 3.3. Thuật toán lần 2 – Multi-Key Quicksort + Memory Pool

**Vấn đề lần 1:** `std::string` + `std::vector` gây cấp phát động liên tục, cache miss, bộ nhớ phụ lớn. Quick Sort chuẩn với O(N log N) so sánh × O(L) mỗi phép so sánh = **O(N·L·log N)** — không chấp nhận được khi N, L lớn.

**Các tối ưu lần 2:**

- **Memory Pool (`char pool_buf[MAX_BUF]`):** Tất cả chuỗi liên tiếp trên RAM, `str_ptrs[i]` chỉ lưu con trỏ. Cache-friendly hoàn toàn.
- **Index Sorting:** Chỉ hoán vị chỉ số nguyên O(1), không bao giờ di chuyển dữ liệu chuỗi.
- **Ad-hoc Linked List thay `vector`:** Mảng `head[len]` và `next_idx[i]` phân lô theo độ dài bằng 2 vòng for, tốc độ tiệm cận phần cứng.
- **Multi-Key Quicksort (3-Way):** Tại độ sâu `depth`, chọn pivot là ký tự `str_ptrs[A[l]][depth]`, phân thành 3 phần (<, =, >). Phần = đệ quy với `depth+1`; hai phần còn lại đệ quy với `depth` không đổi. Kết hợp ưu điểm Quick Sort (đơn giản, ít bộ nhớ) và Radix Sort (không lặp lại tiền tố).

**So sánh lần 1 vs lần 2:**

| Tiêu chí | Lần 1 | Lần 2 |
|---|---|---|
| Bộ nhớ | Phân mảnh, cấp phát động | Liên tục (Memory Pool) |
| Cache | Kém | Tuyệt vời |
| Bộ nhớ phụ | Cao (mảng temp) | Thấp (chỉ mảng chỉ số) |
| Hoán vị | Đổi vùng nhớ chuỗi | Hoán vị số nguyên O(1) |
| Đoạn ngắn | Overhead khởi tạo cnt | Nhanh nhờ chia 3 ngôi trực tiếp |

---

*Hết báo cáo.*
