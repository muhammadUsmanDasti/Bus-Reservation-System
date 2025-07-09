**BUS RESERVATION SYSTEM**
This is a console-based **Bus Reservation System** developed in C++ for a first semester final project.
It allows **admin** and **customers** to interact with a text-based system for managing bus routes, booking and cancelling seats, and viewing booking details
**Features:**
 Admin Panel:
- Admin login
- Add a new bus
- View all buses
- View all booking records
- Remove buses
  Customer Panel:
- Customer signup/login
- View available buses
- Book seats (with CNIC & ticket ID)
- Cancel bookings
- View personal bookings
**Other Highlights**
  File handling using `.txt` files for persistent storage
- Bus sorting by departure time (selection sort)
- Simple UI using colored text (`windows.h`)
- Modular code without classes (procedural programming)
- **File Structure**
   busReservationSystem.cpp # Complete source code
   busesDetails.txt # Stores all bus info
   bookingRecord.txt # Stores all booking records
   signUpData.txt # Stores customer credentials
   adminlogin.txt # Stores admin credentials
   .gitignore # Git ignore rules
