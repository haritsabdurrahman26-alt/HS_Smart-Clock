# ⏰ HS Smart Clock (Wemos D1 Mini + OLED)

## 📌 Deskripsi

**HS Smart Clock** adalah jam digital berbasis **Wemos D1 Mini (ESP8266)** dengan tampilan OLED 1.3 inch yang modern dan minimalis.
Jam ini dapat dikonfigurasi melalui **web interface** yang dapat diakses langsung dari smartphone atau laptop tanpa aplikasi tambahan.

Project ini menggabungkan **IoT, embedded system, dan UI design** dalam satu perangkat kecil yang interaktif.

---

## ✨ Fitur Utama

* ⏰ Tampilan jam digital besar dan jelas
* 📅 Menampilkan tanggal (hari, bulan, tahun)
* 🌐 Setting waktu & tanggal via web browser
* 📱 Web UI modern (app-like interface)
* 🎬 Animasi opening “Smart Clock”
* ✨ Efek titik jam berkedip
* 📊 Progress bar per menit (smooth animation)
* 🔌 Standalone (tanpa internet)

---

## 🧰 Hardware yang Digunakan

* Wemos D1 Mini (ESP8266)
* OLED 1.3 inch (SSD1306, I2C)
* Kabel jumper

---

## 🔌 Wiring

| OLED | Wemos D1 Mini |
| ---- | ------------- |
| VCC  | 3.3V          |
| GND  | GND           |
| SCL  | D1            |
| SDA  | D2            |

---

## 🚀 Cara Penggunaan

1. Upload kode ke Wemos D1 Mini
2. Nyalakan perangkat
3. Hubungkan ke WiFi:

   * SSID: **HS Smart Clock**
   * Password: **12345678**
4. Buka browser dan akses:

   ```
   http://192.168.4.1
   ```
5. Atur waktu dan tanggal
6. Jam akan langsung update di OLED

---

## 🧠 Cara Kerja

* Wemos membuat **Access Point (WiFi sendiri)**
* Web server internal menerima input waktu
* Data waktu disimpan di variabel
* OLED menampilkan waktu secara real-time
* Update waktu berjalan setiap 1 menit

---

## 📦 Library yang Digunakan

* U8g2 (untuk OLED display)
* ESP8266WiFi
* ESP8266WebServer

---

## 🎨 Tampilan

* Jam besar di tengah layar
* Tanggal di bagian bawah
* Progress bar di bagian atas
* Animasi intro saat booting

---

## ⚡ Pengembangan Selanjutnya

* 🌐 Sinkronisasi waktu otomatis (NTP)
* 📡 Indikator status WiFi
* 🌙 Mode malam (auto dim)
* 🔔 Fitur alarm
* 🎮 Mini game atau karakter animasi

---

## 📄 Lisensi

Project ini bebas digunakan untuk pembelajaran dan pengembangan lebih lanjut.

---

## 🙌 Author

Dibuat oleh: **Farel**
