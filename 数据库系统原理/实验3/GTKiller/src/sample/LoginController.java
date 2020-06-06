package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.SplitPane;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginController {
    @FXML
    private Button btn_user;
    @FXML
    private Button btn_admin;

    //转换到病人登录界面
    public void on_btn_user_clicked(ActionEvent e) throws IOException {
        Stage currentStage=(Stage)btn_user.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root=FXMLLoader.load(getClass().getResource("UserLogin.fxml"));
        Stage newStage=new Stage();
        newStage.setTitle("用户登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }

    //转换到医生登录界面
    public void on_btn_admin_clicked(ActionEvent e) throws IOException {
        Stage currentStage=(Stage)btn_admin.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root=FXMLLoader.load(getClass().getResource("AdminLogin.fxml"));
        Stage newStage=new Stage();
        newStage.setTitle("管理员登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }
}
