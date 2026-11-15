#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    Graph g;

    // =====================================
    // 1. ADD LOCATIONS
    // =====================================

    g.addLocation("IIT", 250, 300);                    // 0
    g.addLocation("Curzon", 380, 200);                 // 1
    g.addLocation("TSC", 150, 120);                    // 2
    g.addLocation("Central_Library", 200, 180);        // 3
    g.addLocation("Shaheed_Minar", 300, 260);          // 4

    g.addLocation("DU_Arts_Faculty", 420, 280);        // 5
    g.addLocation("Social_Science", 470, 320);         // 6
    g.addLocation("FBS", 520, 300);                    // 7
    g.addLocation("Science_Faculty", 450, 150);        // 8
    g.addLocation("Mokarram_Bhaban", 550, 220);        // 9

    g.addLocation("Teacher_Student_Centre", 130, 100); // 10
    g.addLocation("VC_Office", 350, 100);              // 11
    g.addLocation("Registrar_Building", 330, 150);     // 12
    g.addLocation("Bangla_Academy", 100, 220);         // 13
    g.addLocation("Fine_Arts", 180, 350);              // 14

    g.addLocation("Jagannath_Hall", 250, 420);         // 15
    g.addLocation("Rokeya_Hall", 400, 400);            // 16
    g.addLocation("Surja_Sen_Hall", 500, 400);         // 17
    g.addLocation("Haji_Muhammad_Mohsin_Hall", 580, 350); // 18
    g.addLocation("Shamsunnahar_Hall", 450, 450);      // 19

    g.addLocation("Gymnasium", 650, 300);              // 20
    g.addLocation("Playground", 650, 420);             // 21
    g.addLocation("Nilkhet", 100, 400);                // 22
    g.addLocation("Chankharpul", 300, 500);            // 23


    // =====================================
    // 2. ADD ROADS
    // =====================================

    // -------------------------------------
    // Main Central Area
    // -------------------------------------

    g.addRoad(0, 1, 0.4, 40, false, true);
    g.addRoad(0, 4, 0.5, 35, false, true);
    g.addRoad(1, 4, 0.3, 30, false, true);
    g.addRoad(1, 2, 1.2, 50, false, true);
    g.addRoad(2, 3, 0.4, 25, false, true);

    // Shaheed Minar -> Central Library
    // One-way
    g.addRoad(4, 3, 0.7, 30, true, true);

    // IMPORTANT:
    // Direct Curzon <-> Central Library
    g.addRoad(1, 3, 0.8, 35, false, true);


    // -------------------------------------
    // Academic Area
    // -------------------------------------

    g.addRoad(1, 8, 0.6, 35, false, true);
    g.addRoad(8, 12, 0.4, 30, false, true);
    g.addRoad(12, 11, 0.5, 30, false, true);
    g.addRoad(11, 2, 0.8, 35, false, true);


    // -------------------------------------
    // Faculty Area
    // -------------------------------------

    g.addRoad(3, 5, 0.5, 25, false, true);
    g.addRoad(5, 6, 0.4, 30, false, true);
    g.addRoad(6, 7, 0.5, 35, false, true);
    g.addRoad(7, 9, 0.4, 40, false, true);


    // -------------------------------------
    // Southern Area
    // -------------------------------------

    g.addRoad(2, 13, 0.8, 30, false, true);
    g.addRoad(13, 14, 0.6, 25, false, true);
    g.addRoad(14, 15, 0.7, 30, false, true);


    // -------------------------------------
    // Residential Halls
    // -------------------------------------

    g.addRoad(15, 16, 0.8, 30, false, true);
    g.addRoad(16, 17, 0.6, 30, false, true);
    g.addRoad(17, 18, 0.5, 35, false, true);
    g.addRoad(16, 19, 0.5, 25, false, true);


    // -------------------------------------
    // Sports Area
    // -------------------------------------

    g.addRoad(18, 20, 0.4, 35, false, true);
    g.addRoad(20, 21, 0.5, 40, false, true);
    g.addRoad(17, 21, 0.6, 30, false, true);


    // -------------------------------------
    // Outer Connections
    // -------------------------------------

    g.addRoad(14, 22, 0.8, 35, false, true);
    g.addRoad(15, 23, 0.7, 30, false, true);
    g.addRoad(22, 23, 0.6, 35, false, true);


    // -------------------------------------
    // Additional Connections
    // -------------------------------------

    g.addRoad(5, 12, 0.5, 30, false, true);
    g.addRoad(6, 10, 0.4, 35, false, true);
    g.addRoad(10, 2, 0.3, 25, false, true);


    // =====================================
    // 3. MENU
    // =====================================

    int choice;

    while (true)
    {
        cout << "\n=========================================\n";
        cout << "      MAP NAVIGATION SYSTEM (SPL-1)\n";
        cout << "=========================================\n";

        cout << "1. View Locations\n";
        cout << "2. View Roads & Speed Limits\n";
        cout << "3. Display 2D Visual Map (Canvas)\n";
        cout << "4. Shortest Route & ETA (Dijkstra)\n";
        cout << "5. Shortest Route & ETA (A* Search)\n";
        cout << "6. Compare Dijkstra vs A*\n";
        cout << "7. Toggle Road Status (Open / Block)\n";
        cout << "8. Save Map to File\n";
        cout << "9. Load Map from File\n";
        cout << "10. Test Curzon -> Central Library\n";
        cout << "0. Exit\n";

        cout << "Choice: ";
        cin >> choice;


        // =================================
        // 1. VIEW LOCATIONS
        // =================================

        if (choice == 1)
        {
            g.showLocations();
        }


        // =================================
        // 2. VIEW ROADS
        // =================================

        else if (choice == 2)
        {
            g.showRoads();
        }


        // =================================
        // 3. 2D VISUAL MAP
        // =================================

        else if (choice == 3)
        {
            g.showVisualMap();
        }


        // =================================
        // 4. DIJKSTRA
        // =================================

        else if (choice == 4)
        {
            int s, d;

            cout << "\nEnter start location ID: ";
            cin >> s;

            cout << "Enter destination location ID: ";
            cin >> d;

            g.dijkstra(s, d, true);
        }


        // =================================
        // 5. A*
        // =================================

        else if (choice == 5)
        {
            int s, d;

            cout << "\nEnter start location ID: ";
            cin >> s;

            cout << "Enter destination location ID: ";
            cin >> d;

            g.aStar(s, d, true);
        }


        // =================================
        // 6. COMPARE
        // =================================

        else if (choice == 6)
        {
            int s, d;

            cout << "\nEnter start location ID: ";
            cin >> s;

            cout << "Enter destination location ID: ";
            cin >> d;

            g.compareAlgorithms(s, d);
        }


        // =================================
        // 7. ROAD STATUS
        // =================================

        else if (choice == 7)
        {
            int u, v, status;

            cout << "\nEnter first location ID: ";
            cin >> u;

            cout << "Enter second location ID: ";
            cin >> v;

            cout << "Enter status (1 = Open, 0 = Block): ";
            cin >> status;

            g.setRoadStatus(u, v, status == 1);

            cout << "\nRoad status updated.\n";
        }


        // =================================
        // 8. SAVE MAP
        // =================================

        else if (choice == 8)
        {
            g.saveFile("map.txt");
        }


        // =================================
        // 9. LOAD MAP
        // =================================

        else if (choice == 9)
        {
            g.loadFile("map.txt");
        }


        // =================================
        // 10. TEST CURZON -> LIBRARY
        // =================================

        else if (choice == 10)
        {
            cout << "\n=========================================\n";
            cout << "Testing Curzon -> Central Library\n";
            cout << "=========================================\n";

            cout << "\nExpected shortest route:\n";
            cout << "Curzon -> Central_Library\n";
            cout << "Distance = 0.80 km\n";

            cout << "\nDijkstra Result:\n";
            g.dijkstra(1, 3, true);

            cout << "\nA* Result:\n";
            g.aStar(1, 3, true);
        }


        // =================================
        // 0. EXIT
        // =================================

        else if (choice == 0)
        {
            cout << "\nProgram terminated.\n";
            break;
        }


        // =================================
        // INVALID CHOICE
        // =================================

        else
        {
            cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}