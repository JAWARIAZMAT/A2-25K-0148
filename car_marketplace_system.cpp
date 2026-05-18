#include <iostream>
#include <string>
using namespace std;

class Printable {
public:
    virtual void showDetails() const = 0;
    virtual ~Printable() {}
};

class Searchable {
public:
    virtual bool matchKeyword(string keyword) const = 0;
    virtual ~Searchable() {}
};

class Manageable {
public:
    virtual void doApprove() = 0;
    virtual void doRemove() = 0;
    virtual bool getApprovedStatus() const = 0;
    virtual ~Manageable() {}
};

class Comparable {
public:
    virtual bool isCheaper(const Comparable& other) const = 0;
    virtual ~Comparable() {}
};

class User : public Printable {
private:
    static int totalUserCount;
    int id;
    string fullName;
    string emailAddress;
    string pass;
    const int joinYear;
    
public:
    User() : joinYear(2024) {
        id = 0;
        fullName = "jia";
        emailAddress = "jia@email.com";
        pass = "12345";
        totalUserCount++;
        cout << "User created (default)" << endl;
    }
    
    User(int i, string n, string e, string p, int year) : joinYear(year) {
        id = i;
        fullName = n;
        emailAddress = e;
        pass = p;
        totalUserCount++;
        cout << "User created: " << fullName << endl;
    }
    
    User(const User& other) : joinYear(other.joinYear) {
        id = other.id;
        fullName = other.fullName;
        emailAddress = other.emailAddress;
        pass = other.pass;
        totalUserCount++;
        cout << "User copied: " << fullName << endl;
    }
    
    virtual ~User() {
        totalUserCount--;
        cout << "User removed: " << fullName << endl;
    }
    
    int getID() const { return id; }
    string getName() const { return fullName; }
    string getEmail() const { return emailAddress; }
    int getJoinYear() const { return joinYear; }
    
    void setName(string n) { fullName = n; }
    void setEmail(string e) { emailAddress = e; }
    
    static int getTotalUsers() { return totalUserCount; }
    
    virtual void showRole() const {
        cout << "I am a normal user" << endl;
    }
    
    void showDetails() const {
        cout << "ID: " << id << " | Name: " << fullName << " | Email: " << emailAddress << endl;
    }
    
    friend void seeUserInfo(const User& u);
    friend bool checkSameUser(const User& u1, const User& u2);
};

int User::totalUserCount = 0;

void seeUserInfo(const User& u) {
    cout << "[Friend] Name: " << u.fullName << ", Email: " << u.emailAddress << endl;
}

bool checkSameUser(const User& u1, const User& u2) {
    return u1.id == u2.id;
}

class Buyer : public User {
private:
    int favListings[50];
    int favCount;
    double wallet;
    const int maxFav;
    
public:
    Buyer() : maxFav(50) {
        favCount = 0;
        wallet = 0;
        cout << "Buyer created" << endl;
    }
    
    Buyer(int i, string n, string e, string p, int year, double w) 
        : User(i, n, e, p, year), maxFav(50) {
        favCount = 0;
        wallet = w;
        cout << "Buyer created: " << getName() << " with wallet Rs." << w << endl;
    }
    
    void showRole() const {
        cout << "I am BUYER - I can buy vehicles and save favorites" << endl;
    }
    
    void findVehicle(string brand) {
        cout << "Searching for brand: " << brand << endl;
    }
    
    void findVehicle(string brand, double maxPrice) {
        cout << "Searching for " << brand << " under Rs." << maxPrice << endl;
    }
    
    void findVehicle(string brand, double minPrice, double maxPrice) {
        cout << "Searching for " << brand << " between Rs." << minPrice << " - Rs." << maxPrice << endl;
    }
    
    void addToFav(int listingID) {
        if (favCount < maxFav) {
            favListings[favCount] = listingID;
            favCount++;
            cout << "Listing " << listingID << " added to favorites" << endl;
        }
    }
    
    void showFav() const {
        cout << "\n--- " << getName() << "'s Favorites ---" << endl;
        for (int i = 0; i < favCount; i++) {
            cout << "Listing ID: " << favListings[i] << endl;
        }
    }
    
    double getWalletMoney() const { return wallet; }
    void addWalletMoney(double amt) { wallet += amt; }
    
    friend void addMoneyToBuyer(Buyer& b, double amount);
};

void addMoneyToBuyer(Buyer& b, double amount) {
    b.wallet += amount;
    cout << "[Friend] Added Rs." << amount << " to " << b.getName() << "'s wallet" << endl;
}

class Seller : public User {
private:
    int myListingIDs[50];
    int listingCount;
    double totalEarned;
    double sellerRating;
    const double commission;
    
public:
    Seller() : commission(0.05) {
        listingCount = 0;
        totalEarned = 0;
        sellerRating = 5.0;
        cout << "Seller created" << endl;
    }
    
    Seller(int i, string n, string e, string p, int year, double rating) 
        : User(i, n, e, p, year), commission(0.05) {
        listingCount = 0;
        totalEarned = 0;
        sellerRating = rating;
        cout << "Seller created: " << getName() << " (Rating: " << rating << ")" << endl;
    }
    
    void showRole() const {
        cout << "I am SELLER - I can post vehicles for sale" << endl;
    }
    
    void changeListing(int listingID, double newPrice) {
        cout << "Listing " << listingID << " price changed to Rs." << newPrice << endl;
    }
    
    void changeListing(int listingID, string newTitle) {
        cout << "Listing " << listingID << " title changed to: " << newTitle << endl;
    }
    
    void addListing(int id) {
        if (listingCount < 50) {
            myListingIDs[listingCount] = id;
            listingCount++;
        }
    }
    
    void addEarnings(double amt) { totalEarned += amt; }
    double getEarnings() const { return totalEarned; }
    
    friend void giveSellerBonus(Seller& s);
};

void giveSellerBonus(Seller& s) {
    double bonus = s.totalEarned * 0.10;
    cout << "[Friend] Seller " << s.getName() << " gets bonus: Rs." << bonus << endl;
}

class Admin : public User {
private:
    string level;
    const int adminCode;
    
public:
    Admin() : adminCode(8888) {
        level = "Basic";
        cout << "Admin created" << endl;
    }
    
    Admin(int i, string n, string e, string p, int year, string l) 
        : User(i, n, e, p, year), adminCode(8888) {
        level = l;
        cout << "Admin created: " << getName() << " (Level: " << l << ")" << endl;
    }
    
    void showRole() const {
        cout << "I am ADMIN - I can approve or remove listings" << endl;
    }
    
    void approveListing(int listingID) {
        cout << "Admin approved listing: " << listingID << endl;
    }
    
    void deleteListing(int listingID) {
        cout << "Admin removed listing: " << listingID << endl;
    }
};

class Vehicle : public Printable, public Searchable, public Manageable, public Comparable {
private:
    static int nextVehicleID;
    int vehicleID;
    string brandName;
    string modelName;
    int manufactureYear;
    double priceAmount;
    double mileageKm;
    bool approvedStatus;
    const string vehicleCategory;
    
public:
    Vehicle() : vehicleCategory("General") {
        vehicleID = nextVehicleID++;
        brandName = "Unknown";
        modelName = "Unknown";
        manufactureYear = 2020;
        priceAmount = 0;
        mileageKm = 0;
        approvedStatus = false;
        cout << "Vehicle created - ID: " << vehicleID << endl;
    }
    
    Vehicle(string b, string m, int y, double p, double mil, string cat) 
        : vehicleCategory(cat) {
        vehicleID = nextVehicleID++;
        brandName = b;
        modelName = m;
        manufactureYear = y;
        priceAmount = p;
        mileageKm = mil;
        approvedStatus = false;
        cout << "Vehicle created: " << brandName << " " << modelName << endl;
    }
    
    virtual ~Vehicle() {
        cout << "Vehicle removed: " << brandName << " " << modelName << endl;
    }
    
    int getVID() const { return vehicleID; }
    string getBrand() const { return brandName; }
    string getModel() const { return modelName; }
    int getYear() const { return manufactureYear; }
    double getPrice() const { return priceAmount; }
    void setPrice(double p) { priceAmount = p; }
    static int getNextID() { return nextVehicleID; }
    
    virtual double calcDepreciation() const = 0;
    virtual void showSpecs() const = 0;
    
    void showDetails() const {
        cout << brandName << " " << modelName << " (" << manufactureYear << ") - Rs." << priceAmount << endl;
        cout << "  Mileage: " << mileageKm << " km | Status: " << (approvedStatus ? "Approved" : "Pending") << endl;
    }
    
    bool matchKeyword(string keyword) const {
        return (brandName.find(keyword) != string::npos) || (modelName.find(keyword) != string::npos);
    }
    
    void doApprove() { approvedStatus = true; }
    void doRemove() { approvedStatus = false; }
    bool getApprovedStatus() const { return approvedStatus; }
    
    bool isCheaper(const Comparable& other) const {
        const Vehicle* v = dynamic_cast<const Vehicle*>(&other);
        if (v) return this->priceAmount < v->priceAmount;
        return false;
    }
    
    bool operator==(const Vehicle& other) const {
        return (this->brandName == other.brandName && this->modelName == other.modelName);
    }
    
    bool operator<(const Vehicle& other) const {
        return this->priceAmount < other.priceAmount;
    }
    
    double operator+(const Vehicle& other) const {
        return this->priceAmount + other.priceAmount;
    }
    
    friend void giveDiscount(Vehicle& v, double percent);
};

int Vehicle::nextVehicleID = 100;

void giveDiscount(Vehicle& v, double percent) {
    double discountAmt = v.priceAmount * (percent / 100.0);
    v.priceAmount -= discountAmt;
    cout << "[Friend] Applied " << percent << "% discount. New price: Rs." << v.priceAmount << endl;
}

class Car : public Vehicle {
private:
    int doorsCount;
    string fuelTypeCar;
    bool hasSunroofCar;
    const string bodyStyleCar;
    
public:
    Car() : bodyStyleCar("Sedan") {
        doorsCount = 4;
        fuelTypeCar = "Petrol";
        hasSunroofCar = false;
        cout << "Car created" << endl;
    }
    
    Car(string b, string m, int y, double p, double mil, int doors, string fuel, bool sunroof, string style)
        : Vehicle(b, m, y, p, mil, "Car"), bodyStyleCar(style) {
        doorsCount = doors;
        fuelTypeCar = fuel;
        hasSunroofCar = sunroof;
        cout << "Car created: " << b << " " << m << endl;
    }
    
    double calcDepreciation() const {
        int age = 2026 - getYear();
        double rate = 0.15 * age;
        if (rate > 0.8) rate = 0.8;
        return getPrice() * rate;
    }
    
    void showSpecs() const {
        cout << "\n=== CAR DETAILS ===" << endl;
        cout << "Brand: " << getBrand() << endl;
        cout << "Model: " << getModel() << endl;
        cout << "Year: " << getYear() << endl;
        cout << "Doors: " << doorsCount << endl;
        cout << "Fuel: " << fuelTypeCar << endl;
        cout << "Sunroof: " << (hasSunroofCar ? "Yes" : "No") << endl;
        cout << "Body: " << bodyStyleCar << endl;
        cout << "Price: Rs." << getPrice() << endl;
        cout << "Depreciation: Rs." << calcDepreciation() << endl;
    }
    
    Car operator+(double extraAmount) const {
        Car newCar = *this;
        newCar.setPrice(getPrice() + extraAmount);
        return newCar;
    }
    
    friend void addSunroof(Car& c);
};

void addSunroof(Car& c) {
    if (!c.hasSunroofCar) {
        c.hasSunroofCar = true;
        cout << "[Friend] Added sunroof to " << c.getBrand() << " " << c.getModel() << endl;
    }
    c.setPrice(c.getPrice() * 1.10);
    cout << "[Friend] Car upgraded, new price: Rs." << c.getPrice() << endl;
}

class Bike : public Vehicle {
private:
    int engineCC;
    bool hasABS;
    string bikeCategory;
    const bool hasGear;
    
public:
    Bike() : hasGear(true) {
        engineCC = 150;
        hasABS = false;
        bikeCategory = "Commuter";
        cout << "Bike created" << endl;
    }
    
    Bike(string b, string m, int y, double p, double mil, int cc, bool abs, string cat, bool gear)
        : Vehicle(b, m, y, p, mil, "Bike"), hasGear(gear) {
        engineCC = cc;
        hasABS = abs;
        bikeCategory = cat;
        cout << "Bike created: " << b << " " << m << " (" << cc << "cc)" << endl;
    }
    
    double calcDepreciation() const {
        int age = 2026 - getYear();
        double rate = 0.10 * age;
        if (rate > 0.7) rate = 0.7;
        return getPrice() * rate;
    }
    
    void showSpecs() const {
        cout << "\n=== BIKE DETAILS ===" << endl;
        cout << "Brand: " << getBrand() << endl;
        cout << "Model: " << getModel() << endl;
        cout << "Year: " << getYear() << endl;
        cout << "Engine: " << engineCC << "cc" << endl;
        cout << "ABS: " << (hasABS ? "Yes" : "No") << endl;
        cout << "Type: " << bikeCategory << endl;
        cout << "Has Gear: " << (hasGear ? "Yes" : "No") << endl;
        cout << "Price: Rs." << getPrice() << endl;
        cout << "Depreciation: Rs." << calcDepreciation() << endl;
    }
    
    friend void modifyBike(Bike& b);
};

void modifyBike(Bike& b) {
    b.engineCC = b.engineCC * 1.2;
    cout << "[Friend] Bike engine upgraded to: " << b.engineCC << "cc" << endl;
    if (!b.hasABS) {
        b.hasABS = true;
        cout << "[Friend] ABS added to bike" << endl;
    }
    b.setPrice(b.getPrice() * 1.15);
    cout << "[Friend] Bike modified, new price: Rs." << b.getPrice() << endl;
}

int main() {
    cout << "\n========== VEHICLE MARKETPLACE SYSTEM ==========\n" << endl;
    
    cout << "\n 1. INHERITANCE " << endl;
    cout << "1. User -> Buyer" << endl;
    cout << "2. User -> Seller" << endl;
    cout << "3. User -> Admin" << endl;
    cout << "4. Vehicle -> Car" << endl;
    cout << "5. Vehicle -> Bike" << endl;
    cout << "6. Printable -> User, Vehicle" << endl;
    
    Buyer buyer1(101, "Jawaria", "jawaria@gmail.com", "pass123", 2025, 50000);
    Seller seller1(201, "jia Khan", "jia@email.com", "pass456", 2024, 4.8);
    Admin admin1(301, "Admin User", "admin@system.com", "admin123", 2023, "Super");
    
    cout << "\n>> showRole() output (polymorphism):" << endl;
    buyer1.showRole();
    seller1.showRole();
    admin1.showRole();
    
    cout << "\n2. POLYMORPHISM" << endl;
    
    buyer1.findVehicle("Toyota");
    buyer1.findVehicle("Honda", 25000);
    buyer1.findVehicle("Suzuki", 5000, 15000);
    
    User* uPtr = &buyer1;
    uPtr->showRole();
    uPtr = &seller1;
    uPtr->showRole();
    
    cout << "\n 3. ABSTRACTION " << endl;
    cout << "Abstract classes created:" << endl;
    cout << "- Printable (pure virtual: showDetails)" << endl;
    cout << "- Searchable (pure virtual: matchKeyword)" << endl;
    cout << "- Manageable (pure virtual: doApprove, doRemove)" << endl;
    cout << "- Comparable (pure virtual: isCheaper)" << endl;
    
    Car car1("Toyota", "Camry", 2022, 28000, 15000, 4, "Petrol", true, "Sedan");
    Bike bike1("Honda", "CBR", 2023, 12000, 5000, 600, true, "Sports", true);
    
   
    car1.showDetails();
    car1.showSpecs();
    
    cout << "\n= 4. OPERATOR OVERLOADING" << endl;
    
    Car car2("Toyota", "Camry", 2022, 28000, 12000, 4, "Petrol", true, "Sedan");
    
   
    if (car1 == car2) {
        cout << "car1 and car2 are same model!" << endl;
    }
    
   
    if (car1 < bike1) {
        cout << "Car is cheaper than Bike" << endl;
    } else {
        cout << "Bike is cheaper than Car" << endl;
    }
    
   
    double total = car1 + bike1;
    cout << "Total price of Car + Bike: Rs." << total << endl;
    
    cout << "\n 5. FRIEND FUNCTIONS" << endl;
    
    cout << "\n>> Friend 1: seeUserInfo()" << endl;
    seeUserInfo(buyer1);
    
    cout << "\n>> Friend 2: addMoneyToBuyer()" << endl;
    cout << "Wallet before: Rs." << buyer1.getWalletMoney() << endl;
    addMoneyToBuyer(buyer1, 10000);
    cout << "Wallet after: Rs." << buyer1.getWalletMoney() << endl;
    
    cout << "\n>> Friend 3: giveDiscount()" << endl;
    cout << "Car price before: Rs." << car1.getPrice() << endl;
    giveDiscount(car1, 10);
    
    cout << "\n>> Friend 4: addSunroof()" << endl;
    addSunroof(car1);
    
    cout << "\n>> Friend 5: modifyBike()" << endl;
    modifyBike(bike1);
    
    cout << "\n6. STATIC & CONSTANT MEMBERS=" << endl;
    cout << "Total Users (static): " << User::getTotalUsers() << endl;
    cout << "Next Vehicle ID (static): " << Vehicle::getNextID() << endl;
    cout << "User joinYear (const): " << buyer1.getJoinYear() << endl;
    
  
    
    return 0;
}
