import sys

# Use this file to write your queries. Submit this file in Brightspace after finishing your homework.

# TODO: Write your username and answer to each query as a string in the return statements in the functions below.
# Do not change the function names. 

# Your resulting tables should have the attributes in the same order as appeared in the sample answers.

# Make sure to test that python prints out the strings (your username and SQL queries) correctly.

# usage: python hw1.py

def username():
	return "kotur"

def query1():
	return """
	Select rank, Name, revenue_amount
	From Fortune
	where revenue_amount > (select avg(revenue_amount) from Fortune)
	GROUP BY rank;
	"""

def query2():
	return """
	Select industry, revenue, count(industry) as cnt
	From Fortune
	GROUP BY industry, revenue;
	"""

def query3():
	return """
	Select ref, count(distinct Headquarters) as cnt
	From Fortune
	GROUP BY ref
	HAVING cnt > 1;
	"""

def query4():
	return """
	Select rank, Name, revenue_amount, Employees
	From Fortune
	where revenue_amount > (select avg(revenue_amount) from Fortune)
	AND Employees < (select avg(Employees) from Fortune)
	GROUP BY rank;
	"""

def query5():
	return """
	Select industry, COUNT(*) as number_of_companies 
	from Fortune 
	GROUP by industry 
	having count(*) = (select max(nb_industries) 
	from (select count(industry) as nb_industries 
	from Fortune group by industry) 
	as sub);
	"""

def query6():
	return """
	Select A.Headquarters, A.sum as cnt  
	From (Select Headquarters, SUM(Employees) as sum 
	From Fortune GROUP BY Headquarters
	ORDER BY Employees) as A
    WHERE A.sum=(SELECT SUM(Employees)
	From Fortune GROUP BY Headquarters
	ORDER BY Employees LIMIT 1);
	"""

def query7():
	return """
	Select A.rank, A.name, A.Employees, B.avg_emp
	From Fortune A
    CROSS JOIN (SELECT AVG(employees) as avg_emp FROM Fortune) as B
	Where A.rank > 0 AND A.rank < 6
    GROUP BY A.Name;
	"""

def query8():
	return """
	Select A.Name, A.industry, A.profit 
	From (Select Name, industry, profit
	From Fortune
	GROUP by industry, profit ORDER BY profit desc) as A
	GROUP by industry
	HAVING profit=MAX(A.profit);
	"""

def query9():
	return """
	Select A.Rank, A.Name, A.revenue_amount, (Select AVG(revenue_amount) 
	FROM Fortune B
	WHERE A.Rank < B.Rank) as avg_rev_for_lower_ranks
	FROM Fortune A
	WHERE A.Rank > 0 AND A.Rank < 11
	GROUP BY A.Rank;
	"""

def query10():
	return """
	Select A.name, A.prof as profit_employee_ratio  
	From (Select name, profit/employees as prof 
	From Fortune) as A
    WHERE A.prof=(SELECT MAX(B.prof) as profit_employee_ratio
	From (Select profit/employees as prof From Fortune) as B LIMIT 1);
	"""

def query11():
	return """	
	Select A.name, A.prof as profit_employee_ratio  
	From (Select name, profit/employees as prof 
	From Fortune) as A
    WHERE A.prof=(SELECT MAX(B.prof) as profit_employee_ratio
	From (Select profit/employees as prof From Fortune) as B LIMIT 1)
	OR A.prof=(SELECT MIN(B.prof) as profit_employee_ratio
	From (Select profit/employees as prof From Fortune) as B LIMIT 1)
	ORDER BY profit_employee_ratio desc;
	"""

def query12():
	return """
	Select Rank, Name, profit
	From Fortune
	Where profit > (Select avg(profit) From Fortune)
	AND rank > (Select avg(rank) From Fortune)
	ORDER BY Name;
	"""

def query13():
	return """
	Select A.industry, B.headquarters, cnt1, cnt2
	From (Select industry, count(industry) as cnt1
	From Fortune 
	GROUP BY industry) as A CROSS JOIN (Select headquarters, count(headquarters) as cnt2
	From Fortune 
	GROUP BY headquarters) as B
	HAVING cnt1=cnt2 AND cnt1>1 AND cnt2>1
	ORDER BY industry;
	"""

def query14():
	return """
	Select A.industry as top_industry, MAX(A.profit) as max_total_profit,
	B.industry as bottom_industry, MIN(B.profit) as min_total_profit
	From (Select industry, SUM(profit) as profit 
	From Fortune GROUP BY industry ORDER BY profit desc) as A
	CROSS JOIN (Select industry, SUM(profit) as profit 
	From Fortune GROUP BY industry ORDER BY profit) as B;
	"""

#Do not edit below

def main():
	query_options = {1: query1(), 2: query2(), 3: query3(), 4: query4(), 5: query5(), 6: query6(), 7: query7(), 8: query8(),
		9: query9(), 10: query10(), 11: query11(), 12: query12(), 13: query13(), 14: query14()}

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
