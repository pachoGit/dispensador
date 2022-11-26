<?php

namespace App\Controllers\WEB;

use App\Controllers\BaseController;

use App\Models\API\Config;
use App\Models\API\Detail;

class Home extends BaseController
{
    public function __construct()
    {
        $this->config = new Config;
        $this->detail = new Detail;
    }

    public function index()
    {
        $results = $this->detail
                 ->where('id_config', 1)
                 ->orderBy('time', 'ASC')
                 ->findAll();
        $percentage = $this->config->first();
        return view('dashboard', ['results' => $results, 'percentage' => $percentage]);
    }

    public function delete($id = null)
    {
        $this->detail->delete($id);
        return redirect()->to('web/home');
    }

    public function create($idType = null)
    {
        $data = [
            'time'      => $this->request->getPost('time'),
            'amount'    => $this->request->getPost('amount'),
            'id_type'   => $idType,
            'id_config' => 1
        ];
        $this->detail->insert($data);
        return redirect()->to('web/home');
    }

    public function apiIndex()
    {
        $results = $this->detail
                 ->where('id_config', 1)
                 ->orderBy('time', 'ASC')
                 ->findAll();
        //return var_dump($results);
        $response = '';
        foreach ($results as $result)
        {
            $response .= $result['time'] . ','. $result['amount'] . ',' . $result['id_type'];
            $response .= '-';
        }
        return $response;
    }

    public function apiDelete()
    {
        $data = [
            'time' => $this->request->getGet('time'),
            'amount' => $this->request->getGet('amount'),
            'id_type' => $this->request->getGet('type'),
            'id_config' => 1
        ];
        $register = $this->detail
                  ->where('time', $data['time'])
                  ->where('id_type', $data['id_type'])->first();
        $this->detail->delete($register['id_detail']);
        return json_encode(['Estado' => 'OK', 'Mensaje' => 'Borrado hora']);
    }

    public function apiMount()
    {
        $data = [
            'water_porc' => $this->request->getGet('water_porc'),
            'grain_porc' => $this->request->getGet('grain_porc')
        ];
        $this->config->update(1, $data);
        return json_encode(['Estado' => 'OK', 'Mensaje' => 'Guardado nueva cantidad']);
    }
}
