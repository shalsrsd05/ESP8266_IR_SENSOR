import paho.mqtt.client as mqtt
import mysql.connector
import json

# ---------------- MQTT Configuration ----------------
MQTT_BROKER = "broker.emqx.io"
MQTT_PORT = 1883
MQTT_TOPIC = "esp8266/ir_sensor"

# ---------------- MySQL Configuration ----------------
MYSQL_HOST = "localhost"
MYSQL_USER = "root"
MYSQL_PASSWORD = ""
MYSQL_DATABASE = "ir_monitoring"
MYSQL_TABLE = "ir_data"

# ---------------- Database Initialization ----------------
def init_db():
    conn = mysql.connector.connect(
        host=MYSQL_HOST,
        user=MYSQL_USER,
        password=MYSQL_PASSWORD
    )
    cur = conn.cursor()

    cur.execute(f"CREATE DATABASE IF NOT EXISTS {MYSQL_DATABASE}")
    conn.database = MYSQL_DATABASE

    cur.execute(f"""
        CREATE TABLE IF NOT EXISTS {MYSQL_TABLE} (
            id INT AUTO_INCREMENT PRIMARY KEY,
            ir_status INT,
            status VARCHAR(30),
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    """)

    conn.commit()
    cur.close()
    conn.close()

# ---------------- MQTT Callbacks ----------------
def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code == 0:
        print("Connected to MQTT Broker")
        client.subscribe(MQTT_TOPIC)
    else:
        print("MQTT Connection Failed:", reason_code)

def on_message(client, userdata, msg):
    data = json.loads(msg.payload.decode())

    ir_status = data["ir_status"]
    status_text = data["status"]

    print(f"Received → IR: {ir_status} | {status_text}")
    save_to_db(ir_status, status_text)

# ---------------- Save Data to MySQL ----------------
def save_to_db(ir_status, status_text):
    conn = mysql.connector.connect(
        host=MYSQL_HOST,
        user=MYSQL_USER,
        password=MYSQL_PASSWORD,
        database=MYSQL_DATABASE
    )
    cur = conn.cursor()

    cur.execute(
        f"INSERT INTO {MYSQL_TABLE} (ir_status, status) VALUES (%s, %s)",
        (ir_status, status_text)
    )

    conn.commit()
    cur.close()
    conn.close()

# ---------------- Main Program ----------------
if __name__ == "__main__":
    init_db()

    client = mqtt.Client(
        callback_api_version=mqtt.CallbackAPIVersion.VERSION2
    )
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_forever()
