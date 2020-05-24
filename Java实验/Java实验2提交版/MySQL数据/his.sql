DROP TABLE  IF EXISTS `department`;
CREATE TABLE `department` (
  `depid` char(6),
  `name` char(10) NOT NULL,
  `py` char(8) NOT NULL,
  PRIMARY KEY  (`depid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE  IF EXISTS `patient`;
CREATE TABLE `patient` (
  `pid` char(6),
  `name` char(10) NOT NULL,
  `password` char(8) NOT NULL,
  `balance` decimal(10,2) NOT NULL,
  `last_login_datetime` timestamp  ,
  PRIMARY KEY  (`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;



DROP TABLE  IF EXISTS `doctor`;
CREATE TABLE `doctor` (
  `docid` char(6),
  `depid` char(6) NOT NULL,
  `name` char(10) NOT NULL,
  `py` char(4),
  `password` char(8) NOT NULL,
  `speciallist` boolean NOT NULL,
  `last_login_datetime` timestamp ,
  PRIMARY KEY  (`docid`),
  FOREIGN KEY(`depid`) references `department`(`depid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE  IF EXISTS `register_category`;
CREATE TABLE `register_category` (
  `catid` char(6),
  `name` char(12) NOT NULL,
  `py` char(4) NOT NULL,
  `depid` char(6) NOT NULL,
  `speciallist` boolean NOT NULL,
  `max_reg_number` int NOT NULL,
  `reg_fee`decimal(10,2) NOT NULL,
  PRIMARY KEY  (`catid`),
  FOREIGN KEY(`depid`) references `department`(`depid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE  IF EXISTS `register`;
CREATE TABLE `register` (
  `reg_id` char(6),
  `catid` char(6) NOT NULL,
  `docid` char(6) NOT NULL,
  `pid` char(6) NOT NULL,
  `current_reg_count` int NOT NULL,
  `unreg` boolean NOT NULL,
  `reg_fee` decimal(8,2) NOT NULL,
  `reg_datetime` timestamp NOT NULL,
  PRIMARY KEY  (`reg_id`),
  FOREIGN KEY(`catid`) references `register_category`(`catid`),
  FOREIGN KEY(`docid`) references `doctor`(`docid`),
  FOREIGN KEY(`pid`) references `patient`(`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

