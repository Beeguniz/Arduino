#include <Servo.h>

const int gasSensorPin = A0; // Chân đọc tín hiệu từ cảm biến khí gas
const int relayPin = 7;      // Chân điều khiển relay
const int buzzerPin = 8;     // Chân điều khiển còi chip
const int servoPin1 = 9;     // Chân điều khiển servo 1
const int servoPin2 = 10;    // Chân điều khiển servo 2

Servo servo1;
Servo servo2;

bool doorOpen = false; // Biến để theo dõi trạng thái của cửa

void setup() {
  pinMode(gasSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  servo1.write(180); // Gốc ban đầu của servo 1 (đóng cửa)
  servo2.write(0); // Gốc ban đầu của servo 2 (đóng cửa)

  digitalWrite(relayPin, LOW);  // Tắt relay lúc ban đầu
  digitalWrite(buzzerPin, LOW); // Tắt còi lúc ban đầu
}

void loop() {
  int gasLevel = analogRead(gasSensorPin);
  
  // Tăng mức ngưỡng phát hiện khí gas lên 600
  if (gasLevel > 600) { // Ngưỡng phát hiện rò rỉ khí gas
    digitalWrite(relayPin, HIGH);  // Bật relay để kích hoạt quạt
    digitalWrite(buzzerPin, HIGH); // Bật còi báo động

    // Mở cửa bằng cả hai servo nếu chưa mở
    if (!doorOpen) {
      servo1.write(90); 
      servo2.write(90); 
      doorOpen = true;
    }
  } else {
    digitalWrite(relayPin, LOW);  // Tắt relay
    digitalWrite(buzzerPin, LOW); // Tắt còi

    // Đóng cửa lại bằng cả hai servo nếu chưa đóng
    if (doorOpen) {
      servo1.write(180); 
      servo2.write(0); 
      doorOpen = false;
    }
  }
  delay(1000); // Đọc giá trị cảm biến mỗi giây
}



