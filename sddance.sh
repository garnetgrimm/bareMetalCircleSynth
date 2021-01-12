mkdir -p /mnt/e
mount -t drvfs e: /mnt/e
cp ./kernel.img /mnt/e
umount /mnt/e
