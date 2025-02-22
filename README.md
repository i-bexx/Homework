# Homework
Bu proje, Linux işletim sistemindeki sistem günlüklerini (syslog) anlamak ve bu verileri bağlı liste veri yapısı kullanarak işlemek amacıyla geliştirilmiştir.

Kullanım

----------------------
Bu uygulama, /var/log/syslog dosyasını okuyarak log kayıtlarını bir bağlı liste yapısında saklar ve ardından bu kayıtları ekrana yazdırır.



Kod Yapısı

-----------------------------------
LogNode: Bağlı liste düğümünü temsil eder. Her düğüm bir log kaydı içerir.
createNode: Yeni bir log düğümü oluşturur.
addLog: Logları bağlı listeye ekler.
printLogs: Logları ekrana yazdırır.
freeList: Hafızayı temizler.
