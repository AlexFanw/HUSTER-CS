package sample;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

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

    @FXML
    private TableView<TableVoc> tview_tablevoc;
    @FXML
    private TableColumn<TableVoc,Integer> tc_ID;
    @FXML
    private TableColumn<TableVoc,String> tc_Word;
    @FXML
    private TableColumn<TableVoc,String> tc_Paraphrase;
    @FXML
    private TableColumn<TableVoc,String> tc_Username;

    public void initialize() throws SQLException { //初始化
        setTableVoc();
    }


    public void setTableVoc() throws SQLException { //用于显示生词表
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        String Un = new UserLoginController().getUsername();
        String sql="select * from VocabularyBuilder where Username=?";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        preparedStatement.setString(1,Un);
        ResultSet rs=preparedStatement.executeQuery();
        ObservableList<TableVoc> data= FXCollections.observableArrayList();
        while(rs.next()){
            Integer ID=rs.getInt("ID");
            String Word=rs.getString("Word");
            String Paraphrase=rs.getString("Paraphrase");
            String Username=rs.getString("Username");
            data.add(new TableVoc(ID,Word,Paraphrase,Username));
        }
        tc_ID.setCellValueFactory(new PropertyValueFactory<TableVoc,Integer>("ID"));
        tc_Word.setCellValueFactory(new PropertyValueFactory<TableVoc,String>("Word"));
        tc_Paraphrase.setCellValueFactory(new PropertyValueFactory<TableVoc,String>("Paraphrase"));
        tc_Username.setCellValueFactory(new PropertyValueFactory<TableVoc,String>("Username"));
        tview_tablevoc.setItems(data);
        preparedStatement.close();
        connection.close();
    }
}

