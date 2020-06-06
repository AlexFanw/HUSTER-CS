package sample;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class MySQLConnector {
    //连接数据库
    public Connection connection(){
        Connection myConnection=null;
        try{
            myConnection=DriverManager.getConnection("jdbc:mysql://localhost:3306/GTKiller?characterEncoding=utf8","root","123456alex");
            if(myConnection!=null)
                System.out.println("Connection succeeded.");
            else
                System.out.println("Connection failed.");
        }
        catch (SQLException e){
            e.printStackTrace();
        }
        return myConnection;
    }
}
