DROP TABLE IF EXISTS Fortune;
CREATE TABLE Fortune(
   Rank           INTEGER  NOT NULL
  ,Name           VARCHAR(40) NOT NULL PRIMARY KEY
  ,Industry       VARCHAR(30) NOT NULL
  ,Revenue        VARCHAR(10) NOT NULL
  ,Revenue_Amount INTEGER  NOT NULL
  ,Profit         INTEGER  NOT NULL
  ,Employees      INTEGER  NOT NULL
  ,Headquarters   VARCHAR(14) NOT NULL
  ,Ref            INTEGER  NOT NULL
);


INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (1,'Walmart','Retail','Increase',559151,13510,2300000,'United States',4);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (2,'State Grid','Electricity','Increase',386618,5580,896360,'China',5);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (3,'Amazon','Retail Information Technology','Increase',386064,21331,1335000,'United States',6);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (4,'China National Petroleum','Oil and gas','Decrease',283958,4575,1242245,'China',7);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (5,'Sinopec Group','Oil and gas','Decrease',283728,6205,553833,'China',8);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (6,'Apple','Electronics','Increase',274515,57411,147000,'United States',9);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (7,'CVS Health','Healthcare','Increase',268706,7179,256500,'United States',10);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (8,'UnitedHealth','Healthcare','Increase',257141,15403,330000,'United States',11);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (9,'Toyota','Automotive','Decrease',256722,21180,366283,'Japan',12);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (10,'Volkswagen','Automotive','Decrease',253965,10104,662575,'Germany',13);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (11,'Berkshire Hathaway','Financials','Increase',254510,42521,360000,'United States',14);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (12,'McKesson','Healthcare','Increase',238228,-4539,67500,'United States',15);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (13,'China State Construction','Construction','Increase',234425,3578,356864,'China',16);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (14,'Saudi Aramco','Oil and gas','Decrease',229766,49287,79800,'Saudi Arabia',17);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (15,'Samsung Electronics','Electronics','Increase',200734,22116,267937,'South Korea',18);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (16,'Ping An Insurance','Financials','Increase',191509,20739,362035,'China',19);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (17,'AmerisourceBergen','Healthcare','Increase',189894,-3409,21500,'United States',20);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (18,'BP','Oil and gas','Decrease',183500,-20305,68100,'United Kingdom',21);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (19,'Royal Dutch Shell','Oil and gas','Decrease',183195,-21680,87000,'Netherlands',22);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (20,'ICBC','Financials','Increase',182794,45783,439787,'China',23);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (21,'Alphabet','Information technology','Increase',182527,40269,144056,'United States',24);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (22,'Foxconn','Electronics','Increase',181945,3457,878429,'Taiwan',25);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (23,'ExxonMobil','Oil and gas','Decrease',181502,-22440,72000,'United States',26);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (24,'Daimler','Automotive','Decrease',175827,4133,288481,'Germany',27);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (25,'China Construction Bank','Financials','Increase',172000,39283,373814,'China',28);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (26,'AT&T','Telecommunications','Decrease',171760,-5176,230760,'United States',29);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (27,'Microsoft','Information technology','Increase',168090,61270,181000,'United States',30);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (28,'Costco','Retail','Increase',166761,4002,214500,'United States',31);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (29,'Cigna','Healthcare','Increase',160401,8458,72963,'United States',32);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (30,'Agricultural Bank of China','Financials','Increase',153885,31293,462592,'China',33);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (31,'Cardinal Health','Healthcare','Increase',152922,-3696,48000,'United States',34);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (32,'Trafigura','Commodities','Decrease',146994,1699,8619,'Singapore',35);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (33,'China Life Insurance','Insurance','Increase',144589,4648,183417,'China',36);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (34,'Glencore','Commodities','Decrease',142338,-1903,87822,'Switzerland',37);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (35,'China Railway Engineering Corporation','Construction','Increase',141384,1639,308483,'China',38);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (36,'Walgreens Boots Alliance','Retail','Increase',139537,456,450000,'United States',39);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (37,'Exor','Holding company','Decrease',136186,-34,263284,'Netherlands',40);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (38,'Allianz','Financials','Increase',136173,7756,150269,'Germany',41);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (39,'Bank of China','Financials','Decrease',134046,27952,309084,'China',42);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (40,'Kroger','Retail','Increase',132498,2585,465000,'United States',2);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (41,'Home Depot','Retail','Increase',132110,12870,504800,'United States',2);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (42,'China Railway Construction','Construction','Increase',131992,1486,364632,'China',2);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (43,'JPMorgan Chase','Financials','Decrease',129503,29131,255351,'United States',43);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (44,'Huawei','Electronics','Increase',129184,9362,197000,'China',44);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (45,'Verizon','Telecommunications','Decrease',128292,17801,132200,'United States',45);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (46,'AXA','Financials','Decrease',128011,3605,96595,'France France',46);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (47,'Ford','Automotive','Decrease',127144,-1279,186000,'United States',47);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (48,'Honda','Automotive','Decrease',124241,6202,211374,'Japan',48);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (49,'General Motors','Automotive','Decrease',122485,6427,155000,'United States',49);
INSERT INTO Fortune(Rank,Name,Industry,Revenue,Revenue_Amount,Profit,Employees,Headquarters,Ref) VALUES (50,'Anthem','Healthcare','Increase',121867,4572,83400,'United States',2);
