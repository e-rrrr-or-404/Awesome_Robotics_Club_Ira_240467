# **Stair-Climbing Robot Design**

## **1. Type of Mechanism: Hybrid (Tracked + Leg Support)**

For this project, I’ve designed a **hybrid stair-climbing robot** that primarily uses **tracks for movement** and includes a **basic leg/lift mechanism** to assist when facing steeper or uneven steps.

### **Why go hybrid?**

Each movement mechanism has its strengths and weaknesses:

- **Wheels** are simple, efficient, and fast—but they’re not great for vertical climbing unless the stairs are shallow and uniform.
- **Legged systems** offer the best flexibility and can adapt to almost any terrain. But they’re complicated to build and require precise control and high energy.
- **Tracked systems** strike a nice balance. They offer **good grip**, **more contact area**, and can handle obstacles like steps better than wheels. But they’re still limited by stair height and shape.

To handle a wider variety of real-world stairs, especially inconsistent ones, I’ve added a **lightweight leg mechanism** to the front. When needed, it lifts or shifts the front of the robot up just enough to give the tracks a better grip. This hybrid approach is relatively **simple to build**, doesn’t need heavy computation like a fully legged robot, and still improves stair-climbing performance significantly.

---

## **2. Stability, Center of Mass, and Power Considerations**

### **Stability:**
Stability is especially important on stairs, since one tilt in the wrong direction could cause the robot to tumble. To manage this:
- The robot has a **wide base** and a **low profile**, which helps distribute weight evenly.
- **Tracks on both sides** increase grip and prevent sideward sliding.
- The **IMU constantly monitors tilt**, and if the robot begins leaning too far forward or backward, the leg mechanism adjusts its posture mid-step.

### **Center of Mass (CoM):**
To keep the center of mass as low and centered as possible:
- Heavier components like the **battery and motor drivers** are placed near the base, between the tracks.
- The **microcontroller and sensors** are mounted higher, but they're relatively light and don’t shift the balance much.
- This keeps most of the weight concentrated at the center, making the robot less likely to tip.

### **Power:**
- The robot runs on a **12V lithium-ion battery pack**, which is a good balance between energy capacity and weight.
- A **power management module** ensures voltage regulation and includes capacitors to handle short bursts of high current—especially during lifting or when climbing higher stairs.
- Motors are chosen based on torque requirements, ensuring they won’t stall under load but also don’t draw too much power unnecessarily.

---

## **3. Sensors and Control Strategy**

### **Sensors Used:**
- **IMU (Inertial Measurement Unit):** Helps track the robot's orientation and detects if it’s tilting or unstable.
- **Ultrasonic Sensor:** Mounted on the front, this measures the distance to the next stair. It’s great for quick obstacle detection.
- **Depth or Stereo Camera:** This helps map out the staircase ahead. With this data, the robot can understand the height and depth of upcoming steps and plan accordingly.
- **IR Sensor:** Positioned at the bottom to detect the stair edge and ensure the robot doesn't overshoot a step or fall off.

### **Control Logic:**
The robot uses a simple decision-making loop:
1. The **camera and ultrasonic sensor** work together to identify upcoming steps—detecting riser height, tread depth, and number of steps.
2. If a step is within trackable height (e.g., < 10cm), the robot climbs using just the tracks.
3. If the step is taller or oddly shaped, the **front leg mechanism activates**. It lifts the front up enough so the tracks can catch the upper step and pull the rest of the robot forward.
4. Throughout the climb, the **IMU constantly feeds orientation data** into a PID controller to keep the robot balanced.
5. The robot adjusts in real time depending on what the sensors see. For instance, if stairs end or curve, the robot stops and reassesses its path.

---
