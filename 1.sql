﻿select * from Spare

select * from InvoiceSpare

select * from UsedSpare

select * from Manufacturer

ALTER TABLE Spare ADD count int default 0

insert into UsedSpare(idService, idSpare, count, date) values(1, 7, 1, '19.04.2014')

insert into InvoiceSpare(idInvoice, idSpare, price, count) values(7, 6, 5.1, 5)

select InvoiceSpare.idSpare, (InvoiceSpare.count - UsedSpare.count) as count from UsedSpare right join InvoiceSpare on UsedSpare.idSpare = InvoiceSpare.idSpare

select Spare.id, Spare.barcode, Spare.name, Spare.idManufacturer, Manufacturer.name from Spare, Manufacturer where Manufacturer.id = Spare.idManufacturer

(select InvoiceSpare.idSpare, (InvoiceSpare.count - UsedSpare.count) as count from UsedSpare, InvoiceSpare where UsedSpare.idSpare = InvoiceSpare.idSpare )
union
(select InvoiceSpare.idSpare, InvoiceSpare.count as count from UsedSpare, InvoiceSpare where UsedSpare.idSpare != InvoiceSpare.idSpare)

select Spare.id, Spare.barcode, Spare.name, Spare.idManufacturer, Manufacturer.name  from Spare, Manufacturer where Spare.id = Manufacturer.idManufacturer

select * from
((select InvoiceSpare.idSpare as unionId, (InvoiceSpare.count - UsedSpare.count) as count from UsedSpare, InvoiceSpare where UsedSpare.idSpare = InvoiceSpare.idSpare )
union
(select InvoiceSpare.idSpare as unionId, InvoiceSpare.count as count from UsedSpare, InvoiceSpare where UsedSpare.idSpare != InvoiceSpare.idSpare)),
(select Spare.id as id, Spare.barcode, Spare.name, Spare.idManufacturer, Manufacturer.name from Spare, Manufacturer where Manufacturer.id = Spare.idManufacturer)
where unionId=id

update Spare set count=InvoiceSpare.count from InvoiceSpare where Spare.id=InvoiceSpare.idSpare


update Spare set count=(select sum(count) from InvoiceSpare where Spare.id=InvoiceSpare.idSpare) from InvoiceSpare where Spare.id=InvoiceSpare.idSpare;
update Spare set count=Spare.count-(select sum(count) from UsedSpare where Spare.id=UsedSpare.idSpare) from UsedSpare where Spare.id=UsedSpare.idSpare;

update Spare set count=(select sum(count) from InvoiceSpare where Spare.id=InvoiceSpare.idSpare) from InvoiceSpare where Spare.id=InvoiceSpare.idSpare;update Spare set count=Spare.count-(select sum(count) from UsedSpare where Spare.id=UsedSpare.idSpare) from UsedSpare where Spare.id=UsedSpare.idSpare;