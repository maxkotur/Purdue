import sys

# Use this file to write your queries. Submit this file in Brightspace after finishing your homework.

#TODO: Write your username and answer to each query as a string in the return statements in the functions below. 
# Do not change the function names. 

#Your resulting tables should have the attributes in the same order as appeared in the sample answers. 

#Make sure to test that python prints out the strings (your username and SQL queries) correctly.

#usage: python hw1.py

def username():
	return "kotur"
    
def query1():
	return """
	Select COUNT(language) AS lan_count
	From language;
	"""

def query2():
	return """
	Select COUNT(team_id) AS cnt 
	From team 
	where meeting_frequency="weekly";
	"""

def query3():
	return """
	Select clearance_id, AVG(salary) AS average_salary 
	from agent 
	where city="Miami" 
	Group BY clearance_id;
	"""
	
def query4():
	return """
	Select clearance_id, AVG(salary) AS average_salary 
	from agent where city="Miami" 
	Group BY clearance_id 
	HAVING average_salary > 200000;
	"""

def query5():
	return """
	Select language from language 
	INNER JOIN languagerel ON languagerel.lang_id = language.lang_id 
	INNER JOIN agent ON agent.agent_id = languagerel.agent_id 
	where agent.city = "Paris" 
	GROUP by language.lang_id;
	"""

def query6():
	return """
	select affiliation.title, agent.agent_id, agent.first, agent.last, agent.city 
	from affiliation 
	INNER JOIN affiliationrel ON affiliation.aff_id=affiliationrel.aff_id
	INNER JOIN agent ON agent.agent_id=affiliationrel.agent_id
	where affiliation.title = "FBI" AND agent.city = "Seattle";
	"""

def query7():
	return """
	select affiliation.title, agent.agent_id, agent.first, agent.last, agent.city, language.language 
	from affiliation 
	INNER JOIN affiliationrel ON affiliation.aff_id=affiliationrel.aff_id
	INNER JOIN agent ON agent.agent_id=affiliationrel.agent_id
	INNER JOIN languagerel ON agent.agent_id=languagerel.agent_id
	INNER JOIN language ON languagerel.lang_id=language.lang_id
	where affiliation.title = "FBI" AND agent.city = "Seattle";
	"""

def query8():
	return """
	Select skill.skill, COUNT(skill.skill) AS cnt
	from skill
	INNER JOIN skillrel ON skill.skill_id=skillrel.skill_id
	GROUP BY skill.skill
	HAVING cnt <= 20;
	"""

def query9():
	return """
	select S1.agent_id, S1.first, S1.last, S1.salary, S1.clearance_id, 
	S2.agent_id, S2.first, S2.last, S2.salary, S2.clearance_id 
	FROM agent S1, agent S2 
	where S1.first=S2.first AND S1.salary=S2.salary AND S1.clearance_id=S2.clearance_id AND S1.agent_id < S2.agent_id;
	"""

def query10():
	return """
	select agent.agent_id, agent.first, agent.last, affiliation.title as affiliation_title
	from agent
	LEFT JOIN affiliationrel ON agent.agent_id=affiliationrel.agent_id
	LEFT JOIN affiliation ON affiliationrel.aff_id=affiliation.aff_id
	where agent.country="Brazil";
	"""
	
def query11():
	return """
	select language.language 
	from language
	INNER JOIN languagerel ON languagerel.lang_id=language.lang_id
	INNER JOIN agent ON agent.agent_id=languagerel.agent_id
	where agent.agent_id=1
	UNION
	select skill.skill
	from skill
	INNER JOIN skillrel ON skillrel.skill_id=skill.skill_id
	INNER JOIN agent ON agent.agent_id=skillrel.agent_id
	where agent.agent_id=1;
	"""

def query12():
	return """
	select CONCAT('affiliation: ', affiliation.title) as aff_city
	from affiliation
	INNER JOIN affiliationrel ON affiliationrel.aff_id=affiliation.aff_id
	INNER JOIN agent ON agent.agent_id=affiliationrel.agent_id
	INNER JOIN teamrel ON teamrel.agent_id=agent.agent_id
	INNER JOIN mission ON mission.team_id=teamrel.team_id
	where mission.name="Media Blanket"
	UNION
	select CONCAT('city: ', agent.city)
	from agent
	INNER JOIN teamrel ON teamrel.agent_id=agent.agent_id
	INNER JOIN mission ON mission.team_id=teamrel.team_id
	where mission.name="Media Blanket";
	"""

#Do not edit below

def main():
	query_options = {1: query1(), 2: query2(), 3: query3(), 4: query4(), 5: query5(), 6: query6(), 7: query7(), 8: query8(), 
		9: query9(), 10: query10(), 11: query11(), 12: query12()}
	
	if len(sys.argv) == 1:
		if username() == "username":
			print("Make sure to change the username function to return your username.")
			return
		else:
			print(username())
		for query in query_options.values():
			print(query)
	elif len(sys.argv) == 2:
		if sys.argv[1] == "username":
			print(username())
		else:
			print(query_options[int(sys.argv[1])])

	
if __name__ == "__main__":
   main()
