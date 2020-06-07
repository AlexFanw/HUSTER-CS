package sample;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.SplitPane;
import javafx.stage.Stage;

import java.io.IOException;

public class VocabularyBuilderController {
    @FXML
    private Button btn_back;
    public void on_btn_back_clicked() throws IOException {
        Stage currentStage=(Stage)btn_back.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root= FXMLLoader.load(getClass().getResource("Book.fxml"));
        Stage newStage=new Stage();
        newStage.setTitle("登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }
}

