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
        $data = $this->config->findAll();
        return view('api_index', ['data' => $data[0]]);
    }
}
