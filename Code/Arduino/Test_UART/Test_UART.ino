
const int LED = 13; //Sử dụng chân 13 trên board để điều khiển đèn LED
String data = "";   //Khai báo biến data lưu lệnh mà người dùng nhập
void setup()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED,LOW); // Ban đầu cho đèn LED tắt
  Serial.begin(9600); // Khai báo sử dụng Serial với tốc độ baud = 9600
}
void loop()
{
  if (Serial.available() > 0)
  {
      char c = Serial.read(); //Đọc từng kí tự
      // Kiểm tra khi kết thúc câu lệnh
      if (c == '\n'){
        Serial.print("Send to Arduino: ");
        Serial.println(data);
        if (data == "a"){
          Serial.print("b");
          digitalWrite(LED,HIGH);
        } else
        if (data == "b"){
          Serial.print("t");
          digitalWrite(LED,LOW);
        }
        data = "";
      } else
        data = data + c;

     //Print byte of data
  }
}