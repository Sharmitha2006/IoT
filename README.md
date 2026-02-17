IoT-Based Classroom Teacher Absence Alert System
Overview:
    The IoT-Based Classroom Teacher Absence Alert System is designed to automatically monitor the presence of teachers in classrooms and notify the staffroom if a teacher is absent beyond a specified time. The system improves classroom supervision, reduces manual monitoring, and ensures timely academic management.
    Problem Statement
    In many institutions, classrooms remain unattended when teachers are delayed or absent, and there is no automatic mechanism to inform the administration. Manual checking consumes time and may cause academic disruption.
    Proposed Solution
    This system uses RFID-based detection and IoT communication to automatically identify whether a teacher is present in the classroom. If the teacher’s RFID tag is not detected within a predefined time (e.g., 5 minutes), an alert message is displayed in the staffroom through a connected IoT device.
    System Architecture
Classroom Unit:
    NodeMCU (ESP8266)
    RFID Reader
    Teacher RFID Tag
Staffroom Unit:
    NodeMCU (ESP8266)
    OLED Display
Communication:
    Wi-Fi network (mobile hotspot / router)
Working Principle:
    Each teacher is assigned an RFID tag.
    At the beginning of the class, the teacher scans the RFID tag using the classroom RFID reader.
    If the RFID tag is detected, the system marks the teacher as present.
    If no RFID tag is detected within the predefined time, an alert is sent through Wi-Fi to the staffroom NodeMCU.
    The staffroom OLED display shows the classroom absence alert.
Components Used:
    NodeMCU ESP8266 (2 units)
    RFID Reader Module
    RFID Tags
    OLED Display
    Jumper wires
    Power supply (USB / Power bank)
Advantages:
    Reduces manual monitoring
    Real-time alerts
    Low-cost IoT implementation
    Easy to deploy in educational institutions
Future Enhancements:
    Mobile notification to staff
    Integration with attendance management systems
    Cloud-based monitoring dashboard
    Multi-classroom centralized monitoring
