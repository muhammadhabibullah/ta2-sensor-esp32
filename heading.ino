
String getMataAngin(double course) {
   static const char* directions[] = {
        "Utara", "Utara - Timur Laut", "Timur Laut", "Timur Laut", 
        "Timur", "Timur - Tenggara", "Tenggara", "Selatan Tenggara", 
        "Selatan", "Selatan Daya", "Barat Daya", "Barat Daya", 
        "Barat", "Barat Laut", "Barat Laut", "Utara - Barat Laut"
    };
    int direction = (int)((course + 11.25f) / 22.5f);
    return directions[direction % 16];
}
