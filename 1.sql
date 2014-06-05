select 
	  Aggregate.name
	, Aggregate.number
	, AggregateType.id
	, AggregateType.name
	, Car.id
	, Car.name
from 
	  Aggregate
	, AggregateType
	, Car 
where
	    Aggregate.id=1
	and AggregateType.id=Aggregate.idAggregateType
	and Car.id=Aggregate.idCar

select Person.name, Person.surname, Person.patronymic, Phones.phone from Person, Phones where Phones.idPerson=Person.id and Person.id = 

select * from AggregateType

select * from Car

select * from Spare

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



select * from Service
select * from Aggregate
select * from Phones

insert into Phones(idPerson, phone) values(4, 'К Т 1 2')

select
	  Service.id
	, Service.idServiceState
	, Service.boxNumber
	, Service.StartDate
	, Service.endDate
	, Service.price
	, Aggregate.name as aggregateName
	, Person.name as personName
	, Person.patronymic as personPatronymic
	, Phones.phone as personPhone
 from Service, Aggregate, Person, Phones
 where
	Aggregate.id = Service.idAggregate
 and    Person.id = Service.idPerson
 and    Person.id = Phones.idPerson


