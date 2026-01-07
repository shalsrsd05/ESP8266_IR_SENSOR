

# IR Sensor Object Detection using ESP8266, MQTT, and MySQL

This project implements a complete **IoT-based object detection and monitoring system** using an **IR sensor** and **ESP8266 (NodeMCU)**. The sensor status data is published to an **MQTT broker** and received by a **Python application**, which stores the data in a **MySQL database** for logging, monitoring, and analysis. The stored data can further be visualized using **Grafana dashboards**.

---

## 1. Project Overview

The system consists of two main components:

### Sender Unit (ESP8266 + IR Sensor)

* Detects object presence using an IR sensor
* Connects to WiFi
* Publishes sensor status (object detected / not detected) to an MQTT broker in JSON format

### Receiver Unit (Python + MQTT + MySQL)

* Subscribes to MQTT topic
* Displays real-time IR sensor status
* Stores sensor data in a MySQL database

This project is suitable for **IoT learning**, **smart monitoring systems**, and **academic mini or major projects**.

---

## 2. Hardware Requirements

* ESP8266 NodeMCU
* IR Sensor Module
* USB Cable
* Jumper Wires
* PC or Laptop with Internet Access

---

## 3. Software Requirements

* Arduino IDE
* Python 3.8 or higher
* MySQL Server (XAMPP / WAMP / Standalone)
* Internet connection

---

## 4. Circuit Connections

| IR Sensor Pin | ESP8266 Pin |
| ------------- | ----------- |
| VCC           | 3V3         |
| OUT           | D5 (GPIO14) |
| GND           | GND         |

**Note:**
Most IR sensors operate at **3.3V**, making them safe for direct connection with ESP8266.

---

## 5. Sender Side (ESP8266) Setup

### 5.1 ESP8266 Board Installation

1. Open Arduino IDE
2. Go to **File → Preferences**
3. Add the following URL in *Additional Board Manager URLs*:

```
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```

4. Go to **Tools → Board → Boards Manager**
5. Install **ESP8266 by ESP8266 Community**

---

### 5.2 Required Arduino Libraries

Install the following libraries using Arduino Library Manager:

* ESP8266WiFi
* PubSubClient (by Nick O'Leary)

---

### 5.3 WiFi Configuration

Update WiFi credentials in the sender code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

---

### 5.4 MQTT Configuration (Sender)

```cpp
const char* mqtt_broker = "broker.emqx.io";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp8266/ir_sensor";
```

---

### 5.5 Uploading Sender Code

1. Open the IR sensor sender `.ino` file
2. Select **Board: NodeMCU 1.0 (ESP-12E Module)**
3. Select correct **COM Port**
4. Set baud rate to **115200**
5. Upload the code
6. Open **Serial Monitor** to verify WiFi and MQTT connection

---

### 5.6 MQTT Data Format

The ESP8266 publishes IR sensor data in JSON format:

```json
{
  "ir_status": 1
}
```

* `1` → Object Detected
* `0` → No Object Detected

---

## 6. Receiver Side (Python + MQTT + MySQL) Setup

### 6.1 Python Dependencies

Install required Python libraries:

```bash
pip install paho-mqtt mysql-connector-python
```

Verify installation:

```bash
python -c "import paho.mqtt, mysql.connector"
```

---

### 6.2 MySQL Configuration

Ensure MySQL Server is running. Default configuration:

```python
MYSQL_HOST = "localhost"
MYSQL_USER = "root"
MYSQL_PASSWORD = ""
MYSQL_DATABASE = "ir_sensor_monitoring"
MYSQL_TABLE = "ir_data"
```

Modify these values if your MySQL credentials differ.

---

### 6.3 Database Initialization

The receiver program automatically:

* Creates the database `ir_sensor_monitoring` if it does not exist
* Creates the table `ir_data` on first run

No manual SQL commands are required.

---

### 6.4 MQTT Configuration (Receiver)

```python
MQTT_BROKER = "broker.emqx.io"
MQTT_PORT = 1883
MQTT_TOPIC = "esp8266/ir_sensor"
```

Ensure the topic matches the ESP8266 sender configuration.

---

### 6.5 Running the Receiver Program

Navigate to the project directory and run:

```bash
python receiver.py
```

Expected output:

```
Connected to MQTT Broker
IR Status: Object Detected
```

---

## 7. Database Schema

**Database Name:** ir_sensor_monitoring
**Table Name:** ir_data

| Column    | Type                              |
| --------- | --------------------------------- |
| id        | INT (Primary Key, Auto Increment) |
| ir_status | INT                               |
| timestamp | DATETIME                          |

---

## 8. Project Files

| File Name                    | Description                             |
| ---------------------------- | --------------------------------------- |
| `ir_sender_code.ino`         | ESP8266 IR sensor MQTT sender           |
| `ir_receiver_python_code.py` | Python MQTT receiver with MySQL storage |

---

## 9. Common Issues and Troubleshooting

| Issue                   | Solution                       |
| ----------------------- | ------------------------------ |
| No detection            | Check IR sensor alignment      |
| ESP8266 resets          | Use stable power supply        |
| MQTT not receiving data | Verify topic and internet      |
| MySQL access denied     | Check credentials              |
| Incorrect readings      | Adjust IR sensor potentiometer |

---

## 10. Applications

* Smart Dustbin Monitoring
* Object Counting Systems
* Smart Door / Entry Detection
* Obstacle Detection
* Industrial Automation

---

## 11. Future Enhancements

* Threshold-based alerts
* Grafana dashboard visualization
* Web dashboard using Flask
* Cloud database integration
* Mobile notifications

---

## 12. Author

**SHALINI DEVI R**
GitHub: [https://github.com/shalsrsd05](https://github.com/shalsrsd05)

---

## 13. License

This project is intended for **educational and academic use**.


