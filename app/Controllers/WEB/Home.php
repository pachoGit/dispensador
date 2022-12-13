<?php

namespace App\Controllers\WEB;

use App\Controllers\BaseController;

use App\Models\API\Config;
use App\Models\API\Detail;
use App\Models\API\Logemail;

class Home extends BaseController
{
    public function __construct()
    {
        $this->config = new Config;
        $this->detail = new Detail;
        $this->logemail = new Logemail;
        $this->email = \Config\Services::email();
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

        if (intval($data['water_porc']) <= 10 || intval($data['grain_porc']) <= 10)
        {
            $result = $this->logemail->orderBy('created_at', 'DESC')->first();

            $last = new \DateTime($result['created_at']);
            $datetime = new \DateTime('now', new \DateTimeZone('America/Lima'));
            $interval = $last->diff($datetime);
            $time = intval($interval->format('%H'));

            if ($time > 1)
            {
                $dataEmail = $this->sendMail($data['grain_porc'], $data['water_porc']);
                $this->logemail->insert(['description' => 'Log Email']);
            }
            return json_encode(['Estado' => 'OK', 'Mensaje' => 'Guardado nueva cantidad' . $dataEmail]);
        }
        return json_encode(['Estado' => 'OK', 'Mensaje' => 'Guardado nueva cantidad']);
    }

    public function sendMail($grain, $water)
    {
        $message = 'Los recursos se estan agotando: \n';
        $message .= 'Porcentaje del agua: ' . $water . '\n';
        $message .= 'Porcentaje del maiz: ' . $grain;

        $this->email->setTo('hcpazv@alumno.unsm.edu.pe');
        $this->email->setFrom('8bcdd928366aa9', 'Contacto Dispensador el TIGRILLO');
        $this->email->setSubject('ESTADO DEL DISPENSADOR');
        $this->email->setMessage($message);
        if ($this->email->send())
            return 'Correo enviado correctamente';
        else
            return 'Correo no enviado' . $this->email->printDebugger(['headers']);

    }
}
