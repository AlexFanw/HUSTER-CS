package sample;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.SplitPane;
import javafx.stage.Stage;

import java.io.IOException;

public class BookController {
    @FXML
    private Button toefl;

    public void on_btn_toefl_clicked() throws IOException {
        Stage currentStage = (Stage) toefl.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root = FXMLLoader.load(getClass().getResource("Toefl.fxml"));
        Stage newStage = new Stage();
        newStage.setTitle("Toefl");
        newStage.setScene(new Scene(root));
        newStage.show();
    }

    @FXML
    private Button gre;

    public void on_btn_gre_clicked() throws IOException {
        Stage currentStage = (Stage) gre.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root = FXMLLoader.load(getClass().getResource("Gre.fxml"));
        Stage newStage = new Stage();
        newStage.setTitle("Gre");
        newStage.setScene(new Scene(root));
        newStage.show();
    }

    @FXML
    private Button new_voc;

    public void on_btn_new_voc_clicked() throws IOException {
        Stage currentStage = (Stage) new_voc.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root = FXMLLoader.load(getClass().getResource("VocabularyBuilder.fxml"));
        Stage newStage = new Stage();
        newStage.setTitle("Gre");
        newStage.setScene(new Scene(root));
        newStage.show();
    }
    @FXML
    private Button btn_back;
    public void on_btn_back_clicked() throws IOException {
        Stage currentStage=(Stage)btn_back.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root= FXMLLoader.load(getClass().getResource("Login.fxml"));
        Stage newStage=new Stage();
        newStage.setTitle("登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }

}