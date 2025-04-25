#include <iostream>
#include <string>
#include <pqxx/pqxx>

int main(int, char **)
{
   try
   {
      pqxx::connection con("dbname=ExampleDB user=postgres password=1234 hostaddr=127.0.0.1 port=5432");
      if (con.is_open())
      {
         std::cout << "Opened database successfully: " << con.dbname() << std::endl;
      }
      else
      {
         std::cout << "Can't open database" << std::endl;
         return 1;
      }

      auto printAllLecturers = [&con]()
      {
         const std::string sqlText = "SELECT * FROM LECTURERS";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "ID = " << iter[0].as<int>() << std::endl;
            std::cout << "FirstName = " << iter[1].as<std::string>() << std::endl;
            std::cout << "SecondName = " << iter[2].as<std::string>() << std::endl;
            std::cout << "DateOfBirth = " << iter[3].as<std::string>() << std::endl;
            std::cout << "Phone = " << iter[4].as<std::string>() << std::endl;
            std::cout << "Email = " << iter[5].as<std::string>() << std::endl;
            std::cout << "Department = " << iter[6].as<int>() << std::endl;
            std::cout << "WorkExperience = " << iter[7].as<int>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto getFiveSubjects = [&con]()
      {
         const std::string sqlText = "select * from Subjects order by Name limit 5;";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "ID = " << iter[0].as<int>() << std::endl;
            std::cout << "Name = " << iter[1].as<std::string>() << std::endl;
            std::cout << "DurationsHours = " << iter[2].as<int>() << std::endl;
            std::cout << "Department = " << iter[3].as<int>() << std::endl;
            std::cout << "Lecturer = " << iter[4].as<int>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto getAllSubjectOfPhysicsDepartment = [&con]()
      {
         const std::string sqlText = "select * from Subjects where department = 1;";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "ID = " << iter[0].as<int>() << std::endl;
            std::cout << "Name = " << iter[1].as<std::string>() << std::endl;
            std::cout << "DurationsHours = " << iter[2].as<int>() << std::endl;
            std::cout << "Department = " << iter[3].as<int>() << std::endl;
            std::cout << "Lecturer = " << iter[4].as<int>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto getDepartmentsId = [&con]()
      {
         const std::string sqlText = "select distinct department from Lecturers order by department;";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "IDepartment = " << iter[0].as<int>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto theAverageDurationOfSubjectsAtTheDepartmentOfChemistry = [&con]()
      {
         const std::string sqlText = "select avg(durationinhours) as duration from Subjects where department = 2;";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "Duration = " << iter[0].as<float>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto getCountOfLecturers = [&con]()
      {
         const std::string sqlText = "select count(*) from Lecturers;";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "Count = " << iter[0].as<std::int64_t>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto minDateOfBirth = [&con]()
      {
         const std::string sqlText = "select min(dateofbirth) from Lecturers;";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "OldDate = " << iter[0].as<std::string>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto getMaxDataOfBirth = [&con]()
      {
         const std::string sqlText = "select max(dateofbirth) from Lecturers;";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "NewDate = " << iter[0].as<std::string>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto getLecturerForSubjects = [&con]()
      {
         const std::string sqlText = "select * from Subjects, Lecturers where Subjects.department = Lecturers.id;";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "Id = " << iter[0].as<int>() << std::endl;
            std::cout << "Name = " << iter[1].as<std::string>() << std::endl;
            std::cout << "DurationInHours = " << iter[2].as<int>() << std::endl;
            std::cout << "Department = " << iter[3].as<int>() << std::endl;
            std::cout << "Lecturer = " << iter[4].as<int>() << std::endl;
            std::cout << "Id = " << iter[5].as<int>() << std::endl;
            std::cout << "FirstName = " << iter[6].as<std::string>() << std::endl;
            std::cout << "SecondName = " << iter[7].as<std::string>() << std::endl;
            std::cout << "DateOfBirth = " << iter[8].as<std::string>() << std::endl;
            std::cout << "Phone = " << iter[9].as<std::string>() << std::endl;
            std::cout << "Email = " << iter[10].as<std::string>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto getInfoAboutSubjects = [&con]()
      {
         const std::string sqlText = "select Subjects.name, Subjects.durationinhours, Departments.name, Lecturers.firstname, Lecturers.secondname from Subjects, Departments, Lecturers where Subjects.department = Departments.id and Subjects.lecturer = Lecturers.id;";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "Name = " << iter[0].as<std::string>() << std::endl;
            std::cout << "DurationInHours = " << iter[1].as<int>() << std::endl;
            std::cout << "Name = " << iter[2].as<std::string>() << std::endl;
            std::cout << "FirstName = " << iter[3].as<std::string>() << std::endl;
            std::cout << "SecondName = " << iter[4].as<std::string>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto getInfoAboutSubjectsWithJoin = [&con]()
      {
         const std::string sqlText = "select Subjects.name, Subjects.durationinhours, Departments.name, Lecturers.firstname, Lecturers.secondname from subjects join departments on Subjects.department = Departments.id join lecturers on Subjects.lecturer = Lecturers.id;";

         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "Name = " << iter[0].as<std::string>() << std::endl;
            std::cout << "DurationInHours = " << iter[1].as<int>() << std::endl;
            std::cout << "Name = " << iter[2].as<std::string>() << std::endl;
            std::cout << "FirstName = " << iter[3].as<std::string>() << std::endl;
            std::cout << "SecondName = " << iter[4].as<std::string>() << std::endl;
            std::cout << std::endl;
         }
      };

      auto getInfoAboutYoungLecturers = [&con]()
      {
         const std::string sqlText = "select lecturers.firstname, lecturers.secondname, lecturers.dateofbirth, lecturers.phone, departments.name  as department, concat_ws(' - ', departments.starttimeofwork, departments.endtimeofwork) as worktime from departments, lecturers where departments.id = lecturers.department order by lecturers.dateofbirth desc limit 3;";
         pqxx::nontransaction N(con);
         pqxx::result R(N.exec(sqlText));

         for (pqxx::result::const_iterator iter = R.begin(); iter != R.end(); ++iter)
         {
            std::cout << "FirstName = " << iter[0].as<std::string>() << std::endl;
            std::cout << "SecondName = " << iter[1].as<std::string>() << std::endl;
            std::cout << "DateOfBirth = " << iter[2].as<std::string>() << std::endl;
            std::cout << "Phone = " << iter[3].as<std::string>() << std::endl;
            std::cout << "Departments = " << iter[4].as<std::string>() << std::endl;
            std::cout << "WorkTime = " << iter[5].as<std::string>() << std::endl;
            std::cout << std::endl;
         }
      };

      

      con.close();
   }
   catch (const std::exception &e)
   {
      std::cerr << e.what() << '\n';
   }
}
