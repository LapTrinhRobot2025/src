// ========= Phần cứng =========
// IR_TX: chân phát IR (nên chọn chân hỗ trợ tone(), ví dụ D3)
// IR_RX: chân analog đọc photodiode (A0) theo sơ đồ phân cực nghịch + R10k

const int IR_TX = 17;
const int IR_RX = 35;

// ========= Kalman 1D đơn giản =========
struct Kalman1D {
  float x;   // ước lượng hiện tại
  float P;   // hiệp phương sai lỗi ước lượng
  float Q;   // nhiễu quá trình (điều chỉnh độ "mượt" vs độ bám)
  float R;   // nhiễu đo (độ tin cậy ADC)
  Kalman1D(float x0=0, float P0=1, float Q_=2.0f, float R_=20.0f)
    : x(x0), P(P0), Q(Q_), R(R_) {}

  float update(float z) {
    // Predict
    P = P + Q; // x = x (mô hình hằng)
    // Update
    float K = P / (P + R);
    x = x + K * (z - x);
    P = (1.0f - K) * P;
    return x;
  }
};

Kalman1D kf(0, 50, 3.0f, 30.0f); // khởi tạo: P0=50, Q=3, R=30 (bạn chỉnh thêm bên dưới)

// ========= Đọc hiệu (khử nền) =========
int readAmbientSubtracted() {
  // Đọc nền (không phát IR)
  digitalWrite(IR_TX, LOW);
  delayMicroseconds(300);
  int offVal = analogRead(IR_RX);

  // Đọc khi bật IR (có thể phát 38kHz để lọc nhiễu)
  tone(IR_TX, 38000);
  delayMicroseconds(400);
  int onVal = analogRead(IR_RX);
  noTone(IR_TX);

  // tắt hẳn trong 1 khoảng nhỏ để ổn định
  delayMicroseconds(300);

  return onVal - offVal; // >0 nghĩa là có phản xạ IR
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_TX, OUTPUT);
  // IR_RX đọc analog -> không cần pinMode
  // Hiệu chỉnh nhanh R bằng cách đo một ít mẫu nền:
  calibrateR(50);  // đo 50 mẫu để ước lượng R (tùy chọn, có thể bỏ)
}

void loop() {
  int z = readAmbientSubtracted();   // đo thô (đơn vị: counts ADC)
  float zf = kf.update((float)z);    // sau Kalman

  Serial.print("raw=");
  Serial.print(z);
  Serial.print("  filt=");
  Serial.print(zf, 2);

  // ví dụ phát hiện vật theo ngưỡng sau khi lọc
  bool detected = (zf > 12.0f); // ngưỡng demo, hãy chỉnh theo thực tế
  Serial.print("  detect=");
  Serial.println(detected ? "YES" : "NO");

  delay(1000);
}

// ========= (Tùy chọn) Tự ước lượng R từ nhiễu đo =========
// Lấy nhiều mẫu đo ở trạng thái "không có vật" để đo phương sai -> gán cho R
void calibrateR(int samples) {
  const int REST_MS = 20;
  long sum = 0;
  long sum2 = 0;
  for (int i = 0; i < samples; ++i) {
    int v = readAmbientSubtracted();
    sum  += v;
    sum2 += (long)v * (long)v;
    delay(REST_MS);
  }
  float mean = (float)sum / samples;
  float var  = (float)sum2 / samples - mean * mean;
  if (var < 1.0f) var = 1.0f; // tránh R=0
  kf.R = var;                 // cập nhật nhiễu đo
  // Giữ Q vừa phải; nếu bạn thấy trễ, tăng Q (ví dụ 3→6)
}
