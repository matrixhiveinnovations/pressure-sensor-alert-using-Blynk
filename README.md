# 🧪 Pressure Sensor Alert System using ESP32 & Blynk

## 📋 Project Description

This project demonstrates a **pressure sensing and alert system** built using the **ESP32 microcontroller**, an **analog pressure sensor**, and the **Blynk IoT platform**. The system reads analog values from a pressure sensor, processes and smooths the data, and sends it to the Blynk mobile app in real-time. If the pressure crosses a critical threshold, the system triggers an **emergency alert** along with a **location message** and turns on an **LED indicator** as a visual warning.

---

## 🧰 Components Used

| Component               | Description                                  |
|------------------------|----------------------------------------------|
| ESP32 Dev Board        | Wi-Fi-enabled microcontroller                |
| Analog Pressure Sensor | Outputs analog voltage based on pressure     |
| LED + Resistor (220Ω)  | For visual emergency indication              |
| Breadboard & Jumpers   | For circuit prototyping                      |
| Mobile with Blynk App  | To receive data and alerts                   |
| Wi-Fi Connection       | Required for ESP32 to connect to Blynk       |

---

## 🔌 Circuit Diagram

- **Pressure Sensor OUT → GPIO 34 (VP)**
- **Pressure Sensor VCC → 3.3V or 5V (depends on sensor)**
- **Pressure Sensor GND → GND**
- **LED Anode (+) → GPIO 2 through 220Ω resistor**
- **LED Cathode (–) → GND**

![image](https://github.com/user-attachments/assets/56fd4d5d-677f-4ba8-97b5-819de2e379b0)


---

## ⚙️ Working Principle

1. The ESP32 continuously reads analog values from the pressure sensor.
2. Values are **smoothed** using exponential averaging to reduce noise.
3. The final value is sent to the **Blynk app** every second using `Blynk.virtualWrite()`.
4. If the pressure value exceeds `1000`, the system:
   - Sends a **log event** ("warning") to the Blynk app.
   - Shows a **location** in the message (hardcoded coordinates).
   - Turns ON an **LED** connected to GPIO 2.
5. When the pressure goes below `1000`, the LED turns OFF and the system resets the alert flag.

---

## 💡 Features in the Code

- 📉 **Sensor Smoothing:** Reduces noise for stable readings.
- 📲 **IoT Dashboard:** Real-time monitoring using the Blynk app.
- 🚨 **Emergency Notification:** Alerts sent only once per event.
- 💡 **LED Indicator:** Local physical alert for high pressure.
- 🌐 **Cloud-Based:** Uses Wi-Fi and Blynk Cloud for remote monitoring.

---

## 📱 Blynk App Setup

1. Download the **Blynk IoT** app.
2. Create a new template and get:
   - `BLYNK_TEMPLATE_ID`
   - `BLYNK_TEMPLATE_NAME`
   - `BLYNK_AUTH_TOKEN`
3. Add a **Value Display** widget and connect it to **Virtual Pin V0**.
4. Create a **Log Event** with ID `"warning"` in Blynk Console.
5. Connect your mobile to the same Wi-Fi network.

---

## 📤 Output on Serial Monitor

```plaintext
Raw: 980 | Smoothed: 981
Raw: 1023 | Smoothed: 1002
--> [Alert Triggered] Emergency notification sent!
# pressure-sensor-alert-using-Blynk
