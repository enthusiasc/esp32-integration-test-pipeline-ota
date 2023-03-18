
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import org.json.JSONException;
import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class ApiIntegrationTests {

    String targetHost = System.getProperty("esp32_hostname");

    @Test
    public void shouldGetDeviceDeviceUptime() throws JSONException, IOException {
        JSONObject response = sendGetRequest("http://" + targetHost + "/getDeviceInformation");
        Integer total_system_uptime_microseconds = response.getInt("device_uptime_microseconds");
        assertTrue(total_system_uptime_microseconds >= 0 );
    }

    @Test
    public void shouldGetTotalFlashMemory() throws JSONException, IOException {
        JSONObject response = sendGetRequest("http://" + targetHost + "/getDeviceInformation");
        Integer total_flash_memory_size_mega_bytes = response.getInt("total_flash_memory_mega_bytes");
        assertTrue(total_flash_memory_size_mega_bytes >= 0 );
    }

    public JSONObject sendGetRequest(String url) throws JSONException, IOException {
        OkHttpClient client = new OkHttpClient();
        Request request = new Request.Builder().url(url).build();
        Response response = client.newCall(request).execute();
        String responseBody = response.body().string();
        return new JSONObject(responseBody);
    }

}
