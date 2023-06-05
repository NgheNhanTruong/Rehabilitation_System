
const int LED = 13; //Sử dụng chân 13 trên board để điều khiển đèn LED
char temp_data;
String record_data="";
void setup()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED,LOW); // Ban đầu cho đèn LED tắt
  Serial.begin(9600); // Khai báo sử dụng Serial với tốc độ baud = 9600
}
void loop()
{
  while (Serial.available() > 0)
  { 
      delay(30);
      char temp_data = Serial.read(); //Đọc từng kí tự
      // Kiểm tra khi kết thúc câu lệnh
      if (temp_data == '#') {break;} 
      record_data = record_data + temp_data;
  }
  if (record_data.length() > 0)
  {
      if (record_data == "abc"){
          digitalWrite(LED,HIGH);
          Serial.println("bat");
      } 
      else if (record_data == "xyz"){
          Serial.println("tat");
          digitalWrite(LED,LOW);
      }
      record_data = "";
  }
}