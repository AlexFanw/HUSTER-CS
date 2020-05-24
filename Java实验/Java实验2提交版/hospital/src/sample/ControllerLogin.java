package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.SplitPane;
import javafx.stage.Stage;

import java.io.IOException;

public class ControllerLogin {
    @FXML
    private Button btn_patient;
    @FXML
    private Button btn_doctor;

    //转换到病人登录界面
    public void on_btn_patient_clicked(ActionEvent e) throws IOException {
        Stage currentStage=(Stage)btn_patient.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root=FXMLLoader.load(getClass().getResource("LoginPatient.fxml"));
        Stage newStage=new Stage();
        newStage.setTitle("病人登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }

    //转换到医生登录界面
    public void on_btn_doctor_clicked(ActionEvent e) throws IOException {
        Stage currentStage=(Stage)btn_doctor.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root=FXMLLoader.load(getClass().getResource("LoginDoctor.fxml"));
        Stage newStage=new Stage();
        newStage.setTitle("医生登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }
}
