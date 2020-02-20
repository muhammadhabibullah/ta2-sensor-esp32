
String getMataAngin(double course) {
   static const char* directions[] = {
        "Utara", "Timur Laut", 
        "Timur", "Tenggara", 
        "Selatan", "Barat Daya", 
        "Barat", "Barat Laut", 
    };
    int direction = (int)((course + 22.5f) / 45);
    return directions[direction % 8];
}
