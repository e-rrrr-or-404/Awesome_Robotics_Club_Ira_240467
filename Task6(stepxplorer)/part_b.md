# **PART-B: What Happens If One Track Fails While Climbing?**

## **1. What would happen to the robot’s motion?**

Let’s say the **left track suddenly stops working** due to a motor issue or something getting stuck in the gears. The **right track would keep moving**, so the robot would start turning **towards the left side**. Since it’s already on stairs, this isn’t just a harmless spin — the robot could end up **twisting out of alignment**, sliding sideways, or even getting stuck halfway between two steps.

Basically, instead of climbing straight, it starts behaving like a car with one wheel stuck

---

## **2. How does this affect balance, path, and tipping?**

- **Balance:** The robot was designed to climb evenly. If one side stops, the weight shifts and it becomes **lopsided**, especially dangerous on stairs where there's not much room for error.
- **Climbing Path:** It would likely start to **veer off to one side** or try to spin in place
- **Tipping Risk:** Pretty high. Since one side is pushing while the other is stuck, the robot could **tilt sideways** and either fall off the stairs or flip backward if it loses grip.

---

## **3. How would you detect the fault?**

Here’s how the robot would know something’s wrong:

- **Motor Encoders:** If the left motor suddenly shows no movement while it's supposed to be turning
- **Current Sensors:** If a motor is trying to move but gets stuck, the current it draws spikes — a sign of a jam.
- **IMU (Inertial Measurement Unit):** If the robot suddenly starts tilting or spinning unexpectedly, the IMU catches it.
- **Mismatch in Speeds:** If one side is clearly moving faster than the other, the robot knows it’s not going straight and can guess that something’s off.

---

## **4. How to stop it from tipping or getting stuck**

### **Before it gets worse:**
- **Pause immediately** if the system detects a motor fault or weird tilt.
- Use the **IMU to keep checking tilt** — if things are getting unbalanced, stop all movement and reassess.

### **If it’s already off-balance:**
- **Stop climbing** and try to **stabilize using the leg mechanism** — it can help hold the robot up while it figures out what to do.

---
