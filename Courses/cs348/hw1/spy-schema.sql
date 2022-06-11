SET FOREIGN_KEY_CHECKS=0;

DROP TABLE IF EXISTS affiliation;
DROP TABLE IF EXISTS affiliationrel;
DROP TABLE IF EXISTS agent;
DROP TABLE IF EXISTS language;
DROP TABLE IF EXISTS languagerel;
DROP TABLE IF EXISTS mission;
DROP TABLE IF EXISTS securityclearance;
DROP TABLE IF EXISTS skill;
DROP TABLE IF EXISTS skillrel;
DROP TABLE IF EXISTS team;
DROP TABLE IF EXISTS teamrel;

CREATE TABLE affiliation (
    aff_id integer NOT NULL,
    title varchar(20),
    description varchar(50),
	PRIMARY KEY (aff_id)
);

CREATE TABLE affiliationrel (
    aff_id integer NOT NULL,
    agent_id integer NOT NULL,
    affiliation_strength varchar(10),
    PRIMARY KEY (aff_id, agent_id)
);

CREATE TABLE agent (
    agent_id integer NOT NULL,
    first varchar(20),
    middle varchar(20),
    last varchar(20),
    address varchar(50),
    city varchar(20),
    country varchar(20),
    salary integer,
    clearance_id integer,
	PRIMARY KEY (agent_id)
);

CREATE TABLE language (
    lang_id integer NOT NULL,
    language varchar(20),
	PRIMARY KEY (lang_id)
);

CREATE TABLE languagerel (
    lang_id integer NOT NULL,
    agent_id integer NOT NULL,
	PRIMARY KEY (lang_id, agent_id)
);

CREATE TABLE mission (
    mission_id integer NOT NULL,
    name varchar(20),
    access_id integer,
    team_id integer,
    mission_status varchar(20),
	PRIMARY KEY (mission_id)
);

CREATE TABLE securityclearance (
    sc_id integer NOT NULL,
    sc_level varchar(20),
    description varchar(50),
	PRIMARY KEY (sc_id)
);

CREATE TABLE skill (
    skill_id integer NOT NULL,
    skill varchar(20),
	PRIMARY KEY (skill_id)
);

CREATE TABLE skillrel (
    skill_id integer NOT NULL,
    agent_id integer NOT NULL,
	PRIMARY KEY (skill_id, agent_id)
);

CREATE TABLE team (
    team_id integer NOT NULL,
    name varchar(20),
    meeting_frequency varchar(20),
	PRIMARY KEY (team_id)
);

CREATE TABLE teamrel (
    team_id integer NOT NULL,
    agent_id integer NOT NULL,
	PRIMARY KEY (team_id, agent_id)
);

SET FOREIGN_KEY_CHECKS=1;