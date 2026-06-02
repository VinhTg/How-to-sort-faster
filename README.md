# BÁO CÁO: PHÂN TÍCH VÀ TỐI ƯU HÓA CÁC THUẬT TOÁN SẮP XẾP

---

## MỤC LỤC

1. [Bài A – Sắp xếp mảng số nguyên](#bài-a--sắp-xếp-mảng-số-nguyên)
   - [1.1. Giải thích thuật toán lần 1](#11-giải-thích-thuật-toán-lần-1)
   - [1.2. Giải thích bộ sinh test](#12-giải-thích-bộ-sinh-test)
   - [1.3. Giải thích thuật toán lần 2](#13-giải-thích-thuật-toán-lần-2)
2. [Bài B – Sắp xếp chuỗi (String Sorting)](#bài-b--sắp-xếp-chuỗi-string-sorting)
   - [2.1. Giải thích thuật toán lần 1](#21-giải-thích-thuật-toán-lần-1)
   - [2.2. Giải thích bộ sinh test](#22-giải-thích-bộ-sinh-test)
   - [2.3. Giải thích thuật toán lần 2](#23-giải-thích-thuật-toán-lần-2)
3. [Bài C – Sắp xếp chuỗi theo độ dài và từ điển](#bài-c--sắp-xếp-chuỗi-theo-độ-dài-và-từ-điển)
   - [3.1. Giải thích thuật toán lần 1](#31-giải-thích-thuật-toán-lần-1)
   - [3.2. Giải thích bộ sinh test](#32-giải-thích-bộ-sinh-test)
   - [3.3. Giải thích thuật toán lần 2](#33-giải-thích-thuật-toán-lần-2)

---

# Bài A – Sắp xếp mảng số nguyên

## 1.1. Giải thích thuật toán lần 1

### 1.1.1. Ý tưởng chung

Chương trình sử dụng **Optimized Quick Sort** để sắp xếp mảng số nguyên. Đây là phiên bản cải tiến của Quick Sort truyền thống, kết hợp nhiều kỹ thuật tối ưu nhằm tăng tốc độ thực thi và giảm nguy cơ rơi vào trường hợp xấu nhất.

Quick Sort hoạt động theo nguyên tắc:

1. Chọn một phần tử làm **pivot**.
2. Chia mảng thành hai phần: các phần tử nhỏ hơn pivot và các phần tử lớn hơn pivot.
3. Đệ quy sắp xếp hai phần đó.

Độ phức tạp trung bình: **O(n log n)**.

---

### 1.1.2. Các kỹ thuật tối ưu hóa

#### A. Median-of-Three Pivot Selection

Trong hàm `partition()`:

```cpp
int mid = left + (right - left) / 2;

if (arr[mid] < arr[left]) swap(arr[mid], arr[left]);
if (arr[right] < arr[left]) swap(arr[right], arr[left]);
if (arr[right] < arr[mid]) swap(arr[right], arr[mid]);

int pivot = arr[mid];
```

Thay vì chọn phần tử đầu, phần tử cuối hoặc phần tử ngẫu nhiên, chương trình lấy **trung vị của ba phần tử**: đầu, giữa và cuối. Ví dụ, với ba giá trị `10, 2, 7`, sau khi sắp xếp thứ tự sẽ là `2, 7, 10` và pivot được chọn là `7`.

**Lợi ích:** Giảm khả năng xuất hiện trường hợp mảng đã sắp xếp tăng dần hoặc giảm dần, vốn khiến Quick Sort suy biến thành O(n²). Median-of-Three tạo ra pivot gần trung tâm hơn, giúp hai nửa sau khi chia cân bằng hơn.

#### B. Hoare Partition Scheme

```cpp
int i = left - 1;
int j = right + 1;

do { i++; } while (arr[i] < pivot);
do { j--; } while (arr[j] > pivot);

swap(arr[i], arr[j]); // lặp đến khi i >= j
```

Hai con trỏ chạy từ hai đầu mảng vào giữa, thực hiện hoán đổi khi cần thiết.

**Lợi ích so với Lomuto Partition:** ít phép swap hơn, ít phép gán hơn, nhanh hơn trong thực tế, và xử lý dữ liệu có nhiều phần tử trùng nhau tốt hơn, dẫn đến hiệu năng thực tế cao hơn đáng kể.

#### C. Insertion Sort cho mảng nhỏ

```cpp
if (right - left < 15)
{
    insertionSort(arr, left, right);
    break;
}
```

Khi kích thước đoạn cần sắp xếp nhỏ hơn 15 phần tử, chương trình không tiếp tục đệ quy mà chuyển sang dùng **Insertion Sort**.

**Lý do:** Mặc dù Insertion Sort có độ phức tạp O(n²), với n rất nhỏ (5, 10, 15 phần tử), nó không có chi phí đệ quy, không cần chọn pivot và không cần partition, nên thực tế nhanh hơn Quick Sort. Đây là kỹ thuật được sử dụng trong nhiều thư viện chuẩn hiện đại.

#### D. Tail Recursion Optimization

```cpp
if (p - left < right - p)
{
    quickSort(arr, left, p);
    left = p + 1;
}
else
{
    quickSort(arr, p + 1, right);
    right = p;
}
```

Chương trình luôn **đệ quy vào nửa nhỏ hơn trước**, chuyển nửa còn lại thành vòng lặp.

**Lợi ích:** Nếu đệ quy thông thường, chiều sâu stack có thể lên đến O(n) trong trường hợp xấu. Kỹ thuật này đảm bảo chiều sâu stack chỉ là O(log n), giúp giảm nguy cơ Stack Overflow, tiết kiệm bộ nhớ và ổn định hơn với dữ liệu lớn.

---

### 1.1.3. Phân tích độ phức tạp

| Trường hợp | Độ phức tạp thời gian |
|---|---|
| Tốt nhất | O(n log n) |
| Trung bình | O(n log n) |
| Xấu nhất | O(n²) |

Nhờ Median-of-Three và Hoare Partition, xác suất gặp trường hợp xấu nhất rất thấp. Bộ nhớ phụ sử dụng: **O(log n)** (nhờ tối ưu đệ quy).

---

### 1.1.4. So sánh với các thuật toán khác và lý do lựa chọn

| Thuật toán | Thời gian TB | Bộ nhớ phụ |
|---|---|---|
| Bubble Sort | O(n²) | O(1) |
| Selection Sort | O(n²) | O(1) |
| Insertion Sort | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n) |
| Heap Sort | O(n log n) | O(1) |
| Quick Sort cơ bản | O(n log n) | O(log n) |
| **Quick Sort tối ưu (chương trình)** | **O(n log n)** | **O(log n)** |

**Lý do lựa chọn Quick Sort tối ưu:**

- **Nhanh nhất trong thực tế:** Mặc dù Heap Sort và Merge Sort cũng đạt O(n log n), Quick Sort thường có hằng số thời gian nhỏ hơn nên chạy nhanh hơn trên dữ liệu thực tế.
- **Không cần bộ nhớ phụ lớn:** Merge Sort cần O(n) bộ nhớ phụ, trong khi chương trình này chỉ cần O(log n) cho ngăn xếp đệ quy.
- **Giảm mạnh khả năng rơi vào O(n²):** Nhờ Median-of-Three và Hoare Partition.
- **Tăng tốc với mảng nhỏ:** Nhờ kết hợp Quick Sort với Insertion Sort.
- **Tiết kiệm bộ nhớ stack:** Nhờ Tail Recursion Optimization.

**Kết luận:** Thuật toán lần 1 là một phiên bản Optimized Quick Sort kết hợp bốn kỹ thuật tối ưu, đạt hiệu năng thực tế rất cao, sử dụng ít bộ nhớ và phù hợp để cài đặt ngay từ lần đầu tiên đối với bài toán sắp xếp mảng số nguyên kích thước lớn.

---

## 1.2. Giải thích bộ sinh test

### Test 1 – Dữ liệu ngẫu nhiên hoàn toàn

**Cách thức sinh:** Chương trình sinh 100.000 số nguyên bằng bộ sinh số giả ngẫu nhiên `mt19937`. Các phép XOR và dịch bit được sử dụng để tăng độ phân tán dữ liệu, đồng thời xen kẽ số dương và số âm nhằm tạo tập dữ liệu có phạm vi giá trị rất lớn và phân bố gần như ngẫu nhiên.

**Thuật toán mục tiêu:** Bộ test này hướng đến các thuật toán sắp xếp bao gồm Quick Sort cài đặt cơ bản (chọn pivot cố định), Merge Sort, Heap Sort, và các thuật toán O(n²) như Bubble Sort, Selection Sort, Insertion Sort.

**Tại sao test này làm tăng thời gian chạy:**
- Với Bubble Sort, Selection Sort, Insertion Sort: thời gian chạy tăng rất mạnh do phải thực hiện khoảng O(n²) phép so sánh và hoán đổi.
- Với Quick Sort cơ bản: dữ liệu ngẫu nhiên khiến thuật toán phải thực hiện đầy đủ các bước phân hoạch và đệ quy trên toàn bộ mảng.
- Với Merge Sort và Heap Sort: dù vẫn đạt O(n log n), kích thước dữ liệu lớn làm tăng số lần so sánh và thao tác bộ nhớ.

> Đây là bộ test ngẫu nhiên quy mô lớn nhằm đánh giá hiệu năng thực tế của các thuật toán sắp xếp trên trường hợp tổng quát.

---

### Test 2 – Dữ liệu có quy luật, phân bố giá trị rộng

**Cách thức sinh:** Chương trình sinh 100.000 số nguyên theo một quy luật xác định. Mỗi phần tử được tạo từ chỉ số `i`, nhân với 256, xen kẽ dấu âm dương và thực hiện thêm phép XOR với `(i << 16)` để tạo ra các giá trị có sự thay đổi mạnh ở các bit cao.

**Thuật toán mục tiêu:** Bộ test này hướng đến Radix Sort, Counting Sort (khi cần xử lý giá trị âm), Quick Sort, Merge Sort và Heap Sort.

**Tại sao test này làm tăng thời gian chạy:**
- Với Radix Sort và Counting Sort: miền giá trị rất rộng khiến việc xử lý trở nên kém hiệu quả hơn so với dữ liệu có phạm vi nhỏ.
- Với Quick Sort: dữ liệu có cấu trúc đặc biệt nên chất lượng phân hoạch phụ thuộc nhiều vào cách chọn pivot.
- Với Merge Sort và Heap Sort: vẫn phải xử lý toàn bộ 100.000 phần tử và thực hiện đầy đủ các bước so sánh, sắp xếp.

> Đây là bộ test dữ liệu có quy luật nhưng phân bố giá trị rộng, dùng để kiểm tra khả năng xử lý của các thuật toán trên tập dữ liệu lớn không hoàn toàn ngẫu nhiên.

---

### Test 3 – Dữ liệu ngẫu nhiên kết hợp dịch bit và XOR nhiều tầng

**Cách thức sinh:** Chương trình sinh 100.000 số nguyên bằng `mt19937`. Mỗi giá trị được tạo qua nhiều phép XOR và dịch bit để tăng độ phân tán. Dấu âm dương được xen kẽ, đồng thời kết hợp với chỉ số phần tử bằng phép XOR để tạo ra tập dữ liệu gần như ngẫu nhiên hoàn toàn.

**Thuật toán mục tiêu:** Quick Sort, Merge Sort, Heap Sort, Radix Sort, Bubble Sort, Selection Sort, Insertion Sort.

**Tại sao test này làm tăng thời gian chạy:**
- Với các thuật toán O(n²): số phép so sánh và hoán đổi tăng cực lớn khi n = 100.000.
- Với Quick Sort: dữ liệu ngẫu nhiên khiến quá trình phân hoạch diễn ra trên toàn bộ cây đệ quy.
- Với Merge Sort và Heap Sort: số phép so sánh đạt gần mức tối đa của trường hợp trung bình.
- Với Radix Sort: sự xuất hiện của cả số âm lẫn số dương cùng miền giá trị rộng làm tăng khối lượng xử lý các chữ số.

> Đây là bộ test ngẫu nhiên kích thước lớn nhằm đánh giá hiệu năng tổng quát trên dữ liệu thực tế không có quy luật đặc biệt.

---

### Test 4 – Trường hợp biên: một phần tử INT_MIN

**Cách thức sinh:** Chương trình sinh một bộ dữ liệu chỉ gồm **1 phần tử** với giá trị `-2147483648`, tức là `INT_MIN` – giá trị nhỏ nhất của kiểu `int` 32-bit.

**Thuật toán mục tiêu:** Tất cả các thuật toán sắp xếp, đặc biệt là Radix Sort hoặc Counting Sort có xử lý số âm, và các chương trình thực hiện phép lấy trị tuyệt đối hoặc đổi dấu phần tử.

**Tại sao test này có thể gây lỗi:**
- Kiểm tra khả năng xử lý khi n = 1, tránh lỗi truy cập ngoài mảng hoặc đệ quy không cần thiết.
- Với một số cài đặt Radix Sort hoặc Counting Sort, việc xử lý `INT_MIN` có thể gây **tràn số (overflow)** khi thực hiện `abs(INT_MIN)` hoặc `-INT_MIN`, vì giá trị đối của `INT_MIN` không biểu diễn được bằng kiểu `int`.
- Giúp phát hiện các lỗi liên quan đến điều kiện biên và xử lý số nguyên cực trị.

> Đây là bộ test biên nhằm kiểm tra tính đúng đắn và độ ổn định của thuật toán khi làm việc với kích thước dữ liệu nhỏ nhất và giá trị nguyên nhỏ nhất có thể xuất hiện.

---

### Test 5 – Dữ liệu ngẫu nhiên có tính tái lập (seed cố định)

**Cách thức sinh:** Chương trình sinh 100.000 số nguyên bằng `mt19937` với **seed cố định** `123456789`. Các giá trị được biến đổi thêm bằng phép XOR và dịch bit để tăng độ phân tán, và dấu âm dương được xen kẽ tạo miền giá trị rộng. Do seed cố định, mọi lần chạy đều cho ra **cùng một bộ dữ liệu**.

**Thuật toán mục tiêu:** Quick Sort, Merge Sort, Heap Sort, Radix Sort, Bubble Sort, Selection Sort, Insertion Sort.

**Tại sao test này làm tăng thời gian chạy:**
- Kích thước dữ liệu lớn (n = 100.000) buộc thuật toán phải xử lý số lượng phần tử rất lớn.
- Dữ liệu phân bố ngẫu nhiên nên không tồn tại cấu trúc đặc biệt để thuật toán tận dụng nhằm tăng tốc.
- Với các thuật toán O(n²), thời gian thực thi tăng rất mạnh.
- Với các thuật toán O(n log n), bộ test tạo điều kiện đánh giá hiệu năng thực tế trên dữ liệu ngẫu nhiên chuẩn.

> Đây là bộ test ngẫu nhiên có **tính tái lập cao**, được sử dụng để đo đạc và so sánh hiệu năng của các thuật toán một cách khách quan và ổn định.

---

## 1.3. Giải thích thuật toán lần 2

### 1.3.1. So sánh tổng quan giữa lần 1 và lần 2

**Lần 1** sử dụng Optimized Quick Sort gồm: Hoare Partition, Median-of-Three, Insertion Sort kết hợp, và Tail Recursion Optimization. Thuật toán hoạt động dựa trên so sánh phần tử, chọn pivot, phân hoạch mảng và đệ quy sắp xếp. Độ phức tạp trung bình: **O(n log n)**.

**Lần 2** chuyển sang sử dụng **LSD Radix Sort Base 256**, kết hợp Fast IO (`fread`, `fwrite`), buffer thủ công, xử lý bit trực tiếp và mảng tĩnh. Thuật toán không sử dụng phép so sánh mà sắp xếp trực tiếp theo từng byte của số nguyên 32-bit. Độ phức tạp: **O(n)**.

---

### 1.3.2. Các hướng tối ưu so với lần 1

#### 1. Chuyển từ Comparison Sort sang Non-Comparison Sort

Lần 1 dùng Quick Sort phải thực hiện rất nhiều phép so sánh. Lần 2 dùng Radix Sort chỉ phân phối dữ liệu theo byte, giảm đáng kể số phép so sánh và số lần rẽ nhánh (branch) của CPU.

#### 2. Giảm độ phức tạp xuống tuyến tính

Quick Sort: O(n log n). Radix Sort: O(4n) – vì số nguyên 32-bit chỉ cần 4 lần xử lý (4 byte).

#### 3. Loại bỏ hoàn toàn đệ quy

Quick Sort vẫn có các lời gọi `quickSort(...)` gây overhead stack. Radix Sort sử dụng vòng lặp hoàn toàn, không tốn chi phí đệ quy.

#### 4. Fast IO

Lần 1 sử dụng `cin / cout`. Lần 2 sử dụng `fread / fwrite` kết hợp buffer lớn, giảm đáng kể thời gian đọc/ghi dữ liệu lớn.

#### 5. Parse số nguyên thủ công

Sử dụng các hàm `read_int()` và `write_int()` thay cho iostream, giúp giảm overhead của thư viện chuẩn C++.

#### 6. Xử lý bit trực tiếp

Sử dụng biểu thức `(v >> shift) & 0xFF` để lấy từng byte. CPU xử lý rất nhanh nhờ các phép dịch bit và mask.

#### 7. Thống kê đồng thời cho 4 pass

Trong một lần duyệt dữ liệu, chương trình thu thập thống kê cho cả 4 byte (`cnt[0]`, `cnt[1]`, `cnt[2]`, `cnt[3]`) cùng lúc, giảm số lần quét mảng.

#### 8. Dùng mảng tĩnh thay cấp phát động

Lần 1 dùng `new int[n]`. Lần 2 dùng `unsigned int arr_a[MAXN]; unsigned int arr_b[MAXN];`. Cách này tránh cấp phát động và tăng cache locality.

#### 9. Tối ưu cache CPU

Radix Sort truy cập dữ liệu tuần tự (`for (i = 0; i < n; i++)`), giúp giảm cache miss và tăng hiệu quả prefetch, trong khi Quick Sort truy cập dữ liệu phân tán hơn.

#### 10. Xử lý số âm bằng XOR

Sử dụng `arr_a[i] ^= 0x80000000` để chuyển thứ tự signed thành unsigned, không cần tách riêng số âm và số dương.

---

### 1.3.3. Kết luận

Phiên bản lần 2 tối ưu hơn lần 1 nhờ: chuyển từ Quick Sort sang Radix Sort, giảm độ phức tạp từ O(n log n) xuống O(n), loại bỏ đệ quy, sử dụng Fast IO, xử lý bit trực tiếp, tối ưu cache CPU và giảm chi phí cấp phát bộ nhớ. Kết quả là tốc độ thực tế nhanh hơn đáng kể trên các bộ test lớn trong bài toán sắp xếp số nguyên.

---

# Bài B – Sắp xếp chuỗi (String Sorting)

## 2.1. Giải thích thuật toán lần 1

### 2.1.1. Tổng quan thuật toán

Thuật toán được sử dụng là **3-Way String Quicksort**. Thuật toán phân hoạch theo ký tự tại vị trí `d`, chia dữ liệu thành ba vùng:

- Nhỏ hơn pivot.
- Bằng pivot.
- Lớn hơn pivot.

Các phần tử thuộc nhóm bằng pivot tiếp tục được xử lý ở độ sâu `d + 1`.

```cpp
void quicksort3way(int lo, int hi, int d) {
    if (hi <= lo) return;

    int lt = lo, gt = hi;
    int v = charAt(a[lo], d);
    int i = lo + 1;

    while (i <= gt) {
        int t = charAt(a[i], d);

        if (t < v)
            swap(a[lt++], a[i++]);
        else if (t > v)
            swap(a[i], a[gt--]);
        else
            i++;
    }

    quicksort3way(lo, lt - 1, d);

    if (v >= 0)
        quicksort3way(lt, gt, d + 1);

    quicksort3way(gt + 1, hi, d);
}
```

---

### 2.1.2. Các kỹ thuật tối ưu hóa

#### A. So sánh từng ký tự

Thuật toán chỉ đọc ký tự tại vị trí `d`. Khi phát hiện khác biệt, quá trình xử lý dừng ngay mà không cần đọc thêm các ký tự phía sau. Nhờ đó, các ký tự thuộc phần tiền tố chung không bị đọc lại nhiều lần.

#### B. Phân hoạch ba chiều

Các chuỗi có cùng ký tự pivot được gom vào cùng một vùng, sau đó chỉ cần một lần đệ quy xuống mức `d + 1` để xử lý tiếp. Điều này giúp giảm số phép so sánh và số lần đệ quy không cần thiết so với Quicksort hai chiều.

#### C. Hàm `charAt()` xử lý chuỗi kết thúc

```cpp
inline int charAt(const string& s, int d) {
    return d < s.length()
           ? (unsigned char)s[d]
           : -1;
}
```

Khi vượt quá độ dài chuỗi, hàm trả về `-1`. Nhờ đó, các chuỗi có độ dài khác nhau được xử lý trực tiếp theo đúng thứ tự từ điển. Ví dụ, chuỗi `"ab"` luôn nhỏ hơn `"abc"` mà không cần điều kiện kiểm tra bổ sung.

#### D. Tối ưu nhập xuất

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

Giúp giảm chi phí nhập xuất trên các bộ dữ liệu lớn.

---

### 2.1.3. So sánh với các thuật toán khác và lý do lựa chọn

| Thuật toán | Độ phức tạp | Hạn chế |
|---|---|---|
| Quicksort truyền thống | O(n·L·log n) | So sánh toàn bộ chuỗi nhiều lần |
| Merge Sort | O(n·L·log n) | Cần O(n) bộ nhớ phụ |
| **3-Way String Quicksort** | **O(n·L) trung bình** | Hiệu quả trên dữ liệu có tiền tố chung |

Điểm quan trọng nhất là tham số `d`: các ký tự thuộc phần tiền tố chung chỉ được xử lý đúng một lần và không bị đọc lại ở các mức đệ quy sau. Nhờ đó thuật toán tận dụng tốt cấu trúc dữ liệu chuỗi và đạt hiệu năng cao nhất trong các phương án cài đặt ở lần thứ nhất.

---

## 2.2. Giải thích bộ sinh test

### 2.2.1. Cấu trúc chung của dữ liệu sinh ra

Mỗi chuỗi được sinh theo dạng:

```
[a × prefA] + [mã nhóm] + [a × prefB] + [đuôi 4 ký tự]
```

Các chuỗi trong cùng một nhóm chỉ khác nhau ở phần đuôi và có **tiền tố chung rất dài**.

### 2.2.2. Thuật toán mục tiêu

Bộ test được thiết kế chủ yếu để làm tăng thời gian chạy của các biến thể **MSD Radix Sort** – nhóm thuật toán thường đạt hiệu năng cao nhất với bài toán sắp xếp chuỗi, nhưng có các điểm yếu đặc trưng:

- Phải khởi tạo bảng đếm ở mỗi mức đệ quy.
- Chỉ phân tách được dữ liệu khi xuất hiện khác biệt tại vị trí đang xét.
- Tiền tố chung càng dài thì số mức đệ quy càng lớn.
- Insertion Sort cho bucket nhỏ vẫn có thể phải đọc lại nhiều ký tự giống nhau.

So với MSD Radix Sort, 3-Way String Quicksort ít bị ảnh hưởng hơn vì không sử dụng bảng đếm và xử lý tốt các nhóm có cùng tiền tố thông qua phân hoạch ba chiều.

### 2.2.3. Phân tích từng test

| Test | Tham số | Chiến lược | Tác động |
|---|---|---|---|
| Test 1 | 3125 × 32, prefix ≈ 90 | Chiều rộng | 3125 bucket, mỗi bucket đệ quy khoảng 90 mức |
| Test 2 | 6250 × 16, prefix ≈ 90 | Ngưỡng Insertion Sort | Bucket kích thước 16 liên tục kích hoạt Insertion Sort |
| Test 3 | 2500 × 32, prefix ≈ 95 | Chiều sâu | Đệ quy khoảng 95 mức trước khi phân tách |
| Test 4 | 2000 × 50, prefix ≈ 96, không xáo trộn | Chiều sâu + bucket lớn | Bucket lớn được giữ nguyên và tiếp tục đệ quy rất sâu |
| Test 5 | Bucket 16/32 xen kẽ, prefix ≈ 70 | Kết hợp | Tác động đồng thời lên đệ quy và Insertion Sort |

### 2.2.4. Chiến lược tổng thể

- Test 1 và Test 2 tấn công theo **chiều rộng** bằng cách tạo rất nhiều bucket.
- Test 3 và Test 4 tấn công theo **chiều sâu** bằng cách tạo tiền tố chung cực dài.
- Test 5 kết hợp cả hai hướng.

Mục tiêu chung là làm tăng số mức đệ quy, số lần khởi tạo bảng đếm và số phép so sánh phát sinh trong các bucket nhỏ của MSD Radix Sort.

---

## 2.3. Giải thích thuật toán lần 2

### 2.3.1. Tổng quan

Thuật toán được sử dụng là **MSD Radix Sort kết hợp Hybrid Insertion Sort**.

### 2.3.2. Hạn chế của lần cài đặt thứ nhất

Phiên bản đầu tiên sử dụng 3-Way String Quicksort nhưng vẫn tồn tại một số hạn chế:

- Vẫn thuộc nhóm thuật toán dựa trên phép so sánh.
- Chưa tận dụng trực tiếp việc bảng chữ cái chỉ gồm 26 ký tự.
- Hoán đổi trực tiếp đối tượng `std::string` có chi phí tương đối lớn.
- `cin/cout` vẫn chậm hơn các phương pháp đọc ghi theo bộ đệm.
- Chưa có cơ chế xử lý riêng cho các bucket nhỏ.

Những hạn chế này là cơ sở để phát triển phiên bản thứ hai.

### 2.3.3. Các kỹ thuật tối ưu hóa

#### 1. Chuyển sang MSD Radix Sort

Thay vì so sánh các chuỗi với nhau, thuật toán phân phối trực tiếp dữ liệu vào các bucket dựa trên ký tự đang xét. Mỗi mức đệ quy chỉ cần một lần duyệt tuyến tính O(n) mà không cần thực hiện các phép so sánh chuỗi.

#### 2. Thu nhỏ bảng đếm

Sử dụng `int count[27]` thay cho `int count[256]`. Bảng đếm nhỏ hơn khoảng 9,5 lần và dễ nằm trong cache CPU hơn.

#### 3. Sắp xếp trên mảng chỉ số

```cpp
int idx1[MAXN];
int idx2[MAXN];
```

Thuật toán chỉ di chuyển các giá trị nguyên thay vì di chuyển toàn bộ chuỗi, giảm đáng kể chi phí dữ liệu.

#### 4. Hybrid Insertion Sort cho bucket nhỏ

Khi `n <= 32`, thuật toán chuyển sang Insertion Sort, tránh chi phí khởi tạo bảng đếm và đệ quy đối với các bucket nhỏ.

#### 5. So sánh từ đúng độ sâu hiện tại

```cpp
inline bool less_suffix(const char* a, const char* b, int depth)
```

Khi Insertion Sort được gọi ở độ sâu `depth`, các ký tự trước đó đã chắc chắn giống nhau. Nếu sử dụng `strcmp()`, toàn bộ phần tiền tố sẽ bị đọc lại. Với tiền tố dài khoảng 90 ký tự, mỗi phép so sánh sẽ lãng phí khoảng 90 lần đọc ký tự. Hàm `less_suffix()` bắt đầu trực tiếp tại vị trí `depth`, loại bỏ hoàn toàn chi phí này.

#### 6. Đọc dữ liệu bằng `fread`

```cpp
fread(in_buf, 1, MAX_BUF - 1, stdin);
```

Toàn bộ dữ liệu được đưa vào một bộ đệm duy nhất. Các chuỗi chỉ được lưu dưới dạng con trỏ `strings[i] = &in_buf[p]`, không phát sinh cấp phát động cho từng chuỗi.

#### 7. Bộ đệm xuất riêng

Kết quả được ghi vào `char out_buf[MAX_BUF]` và xuất bằng `fwrite()`, giúp giảm đáng kể số lần gọi hàm xuất dữ liệu của hệ điều hành.

#### 8. Lưu trước độ dài chuỗi

```cpp
str_len[i] = p - st;
```

Khi xuất dữ liệu, chương trình không cần gọi lại `strlen()` cho từng chuỗi.

### 2.3.4. Kết quả cải thiện

So với phiên bản đầu tiên, phiên bản thứ hai: loại bỏ phần lớn các phép so sánh chuỗi, giảm chi phí di chuyển dữ liệu, tận dụng đặc điểm bảng chữ cái gồm 26 ký tự, tối ưu nhập xuất bằng bộ đệm lớn, và tối ưu bucket nhỏ bằng Hybrid Insertion Sort. Nhờ đó chương trình đạt hiệu năng cao hơn đáng kể trên các bộ dữ liệu kiểm thử đã xây dựng.

---

# Bài C – Sắp xếp chuỗi theo độ dài và từ điển

## 3.1. Giải thích thuật toán lần 1

### 3.1.1. Tổng quan các thuật toán được kết hợp

Chương trình kết hợp hai thuật toán sắp xếp để giải quyết bài toán sắp xếp chuỗi.

#### A. Bucket Sort theo độ dài chuỗi

**Cách hoạt động:** Trong hàm `main`, chương trình khởi tạo `vector<string> a[101]` và đẩy các chuỗi vào mảng dựa trên độ dài của chúng (`a[s.size()].push_back(s)`).

**Mục đích:** Chia bài toán lớn thành các bài toán nhỏ hơn. Thay vì sắp xếp toàn bộ danh sách, chương trình chỉ cần sắp xếp các chuỗi có **cùng độ dài** với nhau. Điều này loại bỏ các phép so sánh chênh lệch độ dài không cần thiết trong hàm Radix Sort, giúp code đơn giản hơn.

**Độ phức tạp:** O(N) với N là tổng số chuỗi.

#### B. MSD Radix Sort (Most Significant Digit)

**Cách hoạt động:** Hàm `RadixSort` là thuật toán MSD Radix Sort. Nó sắp xếp các chuỗi dựa trên ký tự đầu tiên (`pos = 0`), nhóm các chuỗi có cùng ký tự đầu tiên lại, rồi gọi đệ quy để sắp xếp tiếp dựa trên ký tự thứ hai (`pos = 1`), v.v.

**Cơ chế lõi – Counting Sort:** Tại mỗi vị trí `pos`, chương trình sử dụng Counting Sort với mảng `cnt[27]` để đếm tần suất 26 chữ cái in thường, tính prefix sum để xác định vị trí đặt của từng chuỗi vào mảng `temp`, rồi gọi đệ quy cho từng khoang nhỏ.

**Độ phức tạp:** Thời gian trung bình O(W), với W là tổng độ dài tất cả các chuỗi.

### 3.1.2. Các hướng tối ưu

MSD Radix Sort rất nhanh về lý thuyết, nhưng có nhược điểm: **chi phí gọi đệ quy và khởi tạo mảng quá lớn đối với các tập dữ liệu nhỏ**.

**Tối ưu 1: Áp dụng ngưỡng cắt (Cut-off) với Insertion Sort / `std::sort`**

Khi chia nhỏ các nhóm chữ cái, sẽ nhanh chóng xuất hiện các mảng con chỉ có 2, 3 hoặc 10 phần tử. Việc khởi tạo mảng `cnt[27]` và vòng lặp đệ quy cho 5 chuỗi sẽ chậm hơn nhiều so với gọi trực tiếp hàm sắp xếp cơ bản. Giải pháp: nếu `r - l < 15`, dừng đệ quy và dùng `std::sort` cho đoạn đó.

**Tối ưu 2: Tối ưu mảng trung gian `temp`**

Việc gán ngược từ `temp` vào `a` bằng vòng lặp swap là ổn, nhưng có thể sao chép nhanh hơn bằng `std::copy` hoặc dùng `std::move` để tránh thao tác copy không cần thiết.

**Tối ưu 3: Tối ưu bộ nhớ cho Bucket**

Thay vì dùng mảng tĩnh `vector<string> a[101]`, có thể duyệt tìm độ dài lớn nhất trong quá trình đọc input, từ đó chỉ duyệt đến giới hạn thực tế, tiết kiệm thời gian khởi tạo và duyệt mảng trống.

---

## 3.2. Giải thích bộ sinh test

### Test 1 – Tiền tố chung dài, cấu trúc nghịch thế

**Cấu trúc dữ liệu đầu vào:** Tổng số chuỗi N = 9999. Mỗi chuỗi gồm tiền tố 2 ký tự sinh tự động theo thứ tự giảm dần từ điển (từ `zz` xuống `aa`), và thân chuỗi 100 ký tự cố định toàn là chữ `a`. Dữ liệu tạo thành chu kỳ lặp lại với mỗi khối gồm 676 chuỗi nghịch thế, tổng cộng khoảng 14.8 khối ghép nối.

**Cơ chế tấn công:**
- **Vô hiệu hóa tiêu chí độ dài:** Ép mọi thuật toán bỏ qua việc so sánh độ dài và tiến thẳng vào so sánh từ điển từng ký tự.
- **Cấu trúc mảng nghịch thế:** Việc lặp lại các chu kỳ giảm dần tạo ra độ lệch phân phối nghiêm trọng đối với các thuật toán chia để trị.

**Thuật toán bị nhắm mục tiêu:**
- Quick Sort cơ bản (Hoare/Lomuto không tối ưu pivot): cây đệ quy bị lệch hoàn toàn, độ phức tạp suy thoái từ O(N log N) xuống O(N²).
- Các thuật toán O(N²) nguyên thủy: TLE do phải gánh khối lượng phép toán hoán vị khổng lồ với N = 9999.

---

### Test 2 – Tiền tố tĩnh dài, điểm phân định ở cuối

**Cấu trúc dữ liệu đầu vào:** Tổng N = 9999, mỗi chuỗi dài chính xác 100 ký tự. Chuỗi gồm: tiền tố 2 ký tự chứa logic tạo nghịch thế, thân chuỗi tĩnh 97 ký tự cố định toàn là `b`, và hậu tố 1 ký tự biến `suffix`.

**Cơ chế tấn công:** Đảo ngược vị trí vùng dữ liệu tĩnh–động, ép CPU của thuật toán phải đọc qua toàn bộ 97 ký tự tĩnh giống hệt nhau trước khi chạm đến điểm phân định (nghịch thế). Điều này đẩy cao chi phí thời gian của mỗi chu kỳ quét.

**Thuật toán bị nhắm mục tiêu:** Các thuật toán so sánh chuỗi tuyến tính, đặc biệt chí mạng với các giải thuật có số lần so sánh tiệm cận O(N²) do phải liên tục xử lý mảng ký tự trùng lặp dài trước khi tìm thấy sự khác biệt.

---

### Test 3 – Phần tử trùng lặp gom nhóm, nghịch thế ngắt nhịp

**Cấu trúc dữ liệu đầu vào:** Tổng N = 9999, độ dài chính xác 100 ký tự. Dữ liệu chia thành các khối, mỗi khối chứa **25 chuỗi giống hệt nhau**. Chuỗi gồm: tiền tố khối 3 ký tự (trong đó `c2` giảm dần tạo chuỗi nghịch thế cục bộ và thỉnh thoảng có bước nhảy vọt reset từ `a` về `z`), và thân chuỗi 97 ký tự cố định toàn là `c`.

**Cơ chế tấn công:**
- **Gom nhóm trùng lặp:** Bơm một lượng lớn phần tử có giá trị bằng nhau đứng liền kề.
- **Ngắt nhịp nghịch thế:** Các bước nhảy vọt làm đứt gãy các chuỗi giảm dần liên tục.

**Thuật toán bị nhắm mục tiêu:**
- Quick Sort không có phân hoạch 3 chiều: hoán đổi dư thừa và chia mảng cực kỳ thiếu đồng đều khi gặp chuỗi trùng lặp, độ phức tạp rớt xuống O(N²).
- TimSort / Hybrid Sorts: bị đánh lừa bởi các bước nhảy vọt, tốn thêm chi phí gộp mảng.

---

### Test 4 – LCP dài 97 ký tự, điểm phân định ở vị trí thứ 98

**Cấu trúc dữ liệu đầu vào:** Tổng N = 9999, dữ liệu chia thành các khối 25 phần tử. Tiền tố dùng chung 97 ký tự gồm `"qwert"` + `c6` + `"b"` + 90 ký tự `"d"`. Ký tự phân định nằm ở vị trí thứ 98 (`suffix`).

**Cơ chế tấn công:**
- **Tiền tố dùng chung dài (LCP):** Khi so sánh trong nội bộ khối 25 phần tử, 97 ký tự đầu hoàn toàn trùng khớp, buộc cỗ máy so sánh quét đến phần tử thứ 98 mới có kết quả.
- **Tấn công răng cưa (Sawtooth):** Đẩy chi phí một phép so sánh đơn lẻ từ O(1) lên giới hạn O(L).

**Thuật toán bị nhắm mục tiêu:**
- Quick Sort tiêu chuẩn: nhạy cảm với dữ liệu có tính thứ tự đặc thù, bị bóp nghẹt bởi thao tác so sánh chuỗi bị kéo dài.
- Natural Merge Sort / TimSort: không thể tìm được các đoạn (runs) tự nhiên đủ tốt, thao tác gộp bị bào mòn tài nguyên bởi LCP dài.

---

### Test 5 – LCP 99 ký tự, xen kẽ khối tăng–giảm

**Cơ chế tấn công:**
- **Tối đa hóa chi phí so sánh (chiến thuật LCP):** Khi so sánh hai chuỗi trong cùng một khối, 99 ký tự đầu tiên hoàn toàn giống nhau (`c1` + `f` + 97 ký tự `e`). Máy tính bắt buộc phải quét đến tận ký tự thứ 100 (`suffix`) mới biết chuỗi nào lớn hơn, đẩy chi phí so sánh lên mức cực đại O(L) thay vì O(1).
- **Đánh lừa logic sắp xếp:** Sắp xếp đan xen "khối tăng dần – nội bộ giảm dần" tạo ra sự phân mảnh liên tục, gãy khúc cứ sau mỗi 24 phần tử.

**Thuật toán bị nhắm mục tiêu:**
- Quick Sort: khi phân hoạch trong nội bộ 24 phần tử của một khối, mảng đang bị ngược (giảm dần) kết hợp chi phí so sánh 100 ký tự gây nghẽn CPU nghiêm trọng.
- TimSort / Natural Merge Sort: bị vô hiệu hóa vì mảng liên tục đổi chiều ở chu kỳ quá ngắn (24 phần tử), ép thuật toán thực hiện vô số thao tác trộn (merge) rác.

---

## 3.3. Giải thích thuật toán lần 2

### 3.3.1. Nền tảng và giới hạn của lần cài đặt thứ nhất

#### Nút thắt cổ chai của so sánh chuỗi

Khi áp dụng các thuật toán sắp xếp chuẩn (Quick Sort, Merge Sort) trực tiếp cho chuỗi, xuất hiện một giới hạn kiến trúc quan trọng. Phép so sánh hai số nguyên `a < b` chỉ mất O(1) ở cấp độ phần cứng. Ngược lại, để so sánh hai chuỗi `S1` và `S2`, CPU phải duyệt qua từng ký tự từ trái sang phải cho đến khi tìm thấy sự khác biệt.

Nếu độ dài trung bình của các chuỗi là L, chi phí cho một lần so sánh là O(L). Với Quick Sort chuẩn có O(N log N) lần so sánh, tổng thời gian thực thi bị đẩy lên thành **O(N log N × L)**. Khi N lên tới hàng triệu và L cũng lớn, chi phí này trở nên không thể chấp nhận được.

#### Hạn chế của Code 1 (MSD Radix Sort + Vector)

- **Chi phí cấp phát động:** Sử dụng `std::string` và `std::vector` đồng nghĩa với việc liên tục gọi `new` và `delete` ngầm (Heap Allocation).
- **Cache Miss:** Các đối tượng `std::string` chứa con trỏ trỏ đến vùng nhớ lưu ký tự nằm rải rác trên RAM. CPU không thể prefetch dữ liệu chuỗi vào cache, gây nghẽn cổ chai bộ nhớ.
- **Chi phí không gian:** Ở mỗi tầng đệ quy, thuật toán cần tạo ra `vector<string> temp` mới. Mặc dù bộ nhớ được giải phóng sau đệ quy, đỉnh điểm mức sử dụng RAM vẫn rất lớn.

---

### 3.3.2. Các kỹ thuật tối ưu trong lần 2

#### A. Memory Pool – Từ bỏ cấp phát động

Thay vì để hệ điều hành cấp phát hàng triệu chuỗi nhỏ lẻ, hệ thống xin hẳn một mảng tĩnh khổng lồ: `char pool_buf[MAX_BUF]`. Tất cả các chuỗi được nối tiếp nhau vào vùng nhớ này. Mảng `str_ptrs[i]` chỉ lưu **con trỏ** trỏ đến điểm bắt đầu của chuỗi thứ i trong Pool.

**Hiệu ứng:** Dữ liệu hoàn toàn liên tục trên RAM. CPU có thể nạp một lúc một khối (cache line) chứa hàng tá ký tự, tăng tốc độ truy xuất lên nhiều lần (Cache-friendly).

#### B. Sắp xếp qua chỉ số (Index Sorting)

Thuật toán không bao giờ hoán vị các chuỗi trong `pool_buf`. Nó lưu các chỉ số từ 0 đến N-1 vào mảng `A`. Khi cần đổi chỗ, chỉ cần đổi chỗ hai số nguyên `A[i]` và `A[j]`. Phép hoán vị chuỗi nặng nề O(L) biến thành phép hoán vị số nguyên **O(1)**.

#### C. Gom nhóm O(N) không dùng Vector

Để phân nhóm độ dài chuỗi mà không dùng `vector<string> a[101]`, hệ thống tạo ra một **danh sách liên kết tự tạo (Ad-hoc Linked List)** bằng hai mảng `head` và `next_idx`:

- `head[len]` giữ chỉ số của chuỗi đầu tiên có độ dài `len`.
- `next_idx[i]` trỏ tới chuỗi tiếp theo có cùng độ dài.

Chỉ với 2 vòng `for` và mảng 1 chiều, dữ liệu được phân lô hoàn hảo với tốc độ tiệm cận mức phần cứng.

#### D. Multi-Key Quicksort (3-Way) – Cốt lõi thuật toán lần 2

Hàm `mkqsort` là sự kết hợp giữa Quick Sort và Radix Sort (**Multi-Key Quicksort**). Thay vì phân phối vào 26 khoang (như MSD Radix Sort), nó chỉ dựa vào **một ký tự duy nhất** tại độ sâu `depth` để chia mảng thành 3 phần.

**Cơ chế phân chia 3 ngôi:** Thuật toán chọn `pivot` là ký tự của chuỗi đầu tiên `str_ptrs[A[l]][depth]`. Quét qua mảng, chia dữ liệu thành:
1. Phần `< pivot` (quản lý bởi con trỏ `lt`)
2. Phần `== pivot` (nằm giữa `lt` và `i`)
3. Phần `> pivot` (quản lý bởi con trỏ `gt`)

**Ví dụ minh họa** tại `depth = 0` với `["cat", "bat", "car", "dog"]`:
- Chọn pivot: `c` (từ `"cat"`).
- `b < c`: đẩy `"bat"` sang trái.
- `c == c`: giữ `"car"` ở giữa.
- `d > c`: đẩy `"dog"` sang phải.

**Đệ quy thông minh:**
- Gọi `mkqsort` cho phần nhỏ hơn với **`depth` không đổi**.
- Gọi `mkqsort` cho phần bằng với **`depth + 1`** (ký tự tại `depth` đã giống nhau, xét ký tự tiếp theo).
- Gọi `mkqsort` cho phần lớn hơn với **`depth` không đổi**.

Việc trượt `depth + 1` chỉ cho phần `==` chính là đặc tính chia để trị tiền tố của Radix Sort, được cài đặt bằng tốc độ và sự đơn giản của Quick Sort.

---

### 3.3.3. So sánh tổng quan giữa Code 1 và Code 2

| Tiêu chí | Code 1 (MSD Radix Sort + Vector) | Code 2 (Multi-key Quick Sort + Pool) |
|---|---|---|
| Quản lý bộ nhớ | Rất phân mảnh, cấp phát động liên tục | Cực kỳ liền mạch (Memory Pool) |
| Cache Friendly | Kém (dễ rớt bộ nhớ đệm) | Tuyệt vời (dữ liệu liên tiếp) |
| Bộ nhớ phụ | Cao (cần mảng `temp` bằng kích thước thực tế) | Thấp (chỉ cần mảng chỉ số `A`) |
| Hoán vị (Swap) | Đổi vùng nhớ thật hoặc `std::swap` | Chỉ hoán vị số nguyên (Index O(1)) |
| Xử lý đoạn ngắn | Bị overhead do khởi tạo mảng `cnt` | Cực nhanh nhờ chia 3 ngôi trực tiếp |

---

*Hết báo cáo.*