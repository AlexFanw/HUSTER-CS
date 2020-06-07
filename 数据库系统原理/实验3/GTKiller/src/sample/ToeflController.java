package sample;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.SplitPane;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javax.swing.*;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ToeflController {
    @FXML
    private Button btn_exit;
    @FXML
    private TextField No;
    @FXML
    private TextField Word;
    @FXML
    private TextField Paraphrase;
    @FXML
    private int lastno = -1;
    public void on_btn_start_clicked() throws SQLException { //退出按钮
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        String sql0="select * from Record where Username=? and Bookname=?";
        PreparedStatement preparedStatement0=connection.prepareStatement(sql0);
        String Un = new UserLoginController().getUsername();
        preparedStatement0.setString(1,Un);
        preparedStatement0.setString(2,"toefl");
        ResultSet rs0=preparedStatement0.executeQuery();
        rs0.next();
        lastno = Integer.valueOf(rs0.getString("WordID"));

        String sql="select * from toefl where ID=?";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        preparedStatement.setInt(1, lastno);
        ResultSet rs=preparedStatement.executeQuery();

        rs.next();
        No.setText(rs.getString("ID"));
        Word.setText(rs.getString("Word"));
        Paraphrase.setText(rs.getString("Paraphrase"));
        //Alert alert = new Alert(Alert.AlertType.INFORMATION);
        //alert.setHeaderText(rs.getString("Word"));
        //alert.showAndWait();

        preparedStatement.close();
        connection.close();

    }
    public void on_btn_quit_clicked() throws IOException, SQLException { //退出按钮
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        if(lastno !=-1) {
            String sql = "UPDATE Record SET WordID=? WHERE Username=? and Bookname=?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            String Un = new UserLoginController().getUsername();
            preparedStatement.setInt(1, lastno);
            preparedStatement.setString(2, Un);
            preparedStatement.setString(3, "toefl");
            preparedStatement.executeUpdate();
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("目前已背完"+String.valueOf(lastno)+"个单词");
            alert.showAndWait();
            preparedStatement.close();
            connection.close();
        }
        Stage currentStage=(Stage)btn_exit.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root= FXMLLoader.load(getClass().getResource("Book.fxml")); //转到登录界面
        Stage newStage=new Stage();
        newStage.setTitle("登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }

    public void on_btn_familiar_clicked() throws SQLException { //点击获取挂号号码
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        if(lastno == -1){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("请点击左上角 Start 开始背单词。");
            alert.showAndWait();
            return;
        }
        lastno+=1;

        String sql="select * from toefl where ID=?";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        preparedStatement.setInt(1, lastno);
        ResultSet rs=preparedStatement.executeQuery();

        rs.next();
        No.setText(rs.getString("ID"));
        Word.setText(rs.getString("Word"));
        Paraphrase.setText(rs.getString("Paraphrase"));
        //Alert alert = new Alert(Alert.AlertType.INFORMATION);
        //alert.setHeaderText(rs.getString("Word"));
        //alert.showAndWait();

        preparedStatement.close();
        connection.close();
    }
    public void on_btn_unfamiliar_clicked() throws SQLException { //点击获取挂号号码
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        if(lastno == -1){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("请点击左上角 Start 开始背单词。");
            alert.showAndWait();
            return;
        }
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setHeaderText("该功能待完善");
        alert.showAndWait();
        return;
    }
}
